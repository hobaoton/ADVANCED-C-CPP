#include "parse_json.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Các hàm nội bộ được khai báo static để chỉ sử dụng trong file này */

static void skip_whitespace(const char **json) {
    while (isspace(**json)) {
        (*json)++;
    }
}

static JsonValue *parse_null(const char **json) {
    skip_whitespace(json);
    if (strncmp(*json, "null", 4) == 0) {
        JsonValue *value = (JsonValue *) malloc(sizeof(JsonValue));
        value->type = JSON_NULL;
        *json += 4;
        return value;
    }
    return NULL;
}

static JsonValue *parse_boolean(const char **json) {
    skip_whitespace(json);
    JsonValue *value = (JsonValue *) malloc(sizeof(JsonValue));
    if (strncmp(*json, "true", 4) == 0) {
        value->type = JSON_BOOLEAN;
        value->value.boolean = true;
        *json += 4;
    } else if (strncmp(*json, "false", 5) == 0) {
        value->type = JSON_BOOLEAN;
        value->value.boolean = false;
        *json += 5;
    } else {
        free(value);
        return NULL;
    }
    return value;
}

static JsonValue *parse_number(const char **json) {
    skip_whitespace(json);
    char *end;
    double num = strtod(*json, &end);
    if (end != *json) {
        JsonValue *value = (JsonValue *) malloc(sizeof(JsonValue));
        value->type = JSON_NUMBER;
        value->value.number = num;
        *json = end;
        return value;
    }
    return NULL;
}

static JsonValue *parse_string(const char **json) {
    skip_whitespace(json);
    if (**json == '\"') {
        (*json)++;
        const char *start = *json;
        while (**json != '\"' && **json != '\0') {
            (*json)++;
        }
        if (**json == '\"') {
            size_t length = *json - start;
            char *str = (char *) malloc((length + 1) * sizeof(char));
            strncpy(str, start, length);
            str[length] = '\0';
            JsonValue *value = (JsonValue *) malloc(sizeof(JsonValue));
            value->type = JSON_STRING;
            value->value.string = str;
            (*json)++;
            return value;
        }
    }
    return NULL;
}

static JsonValue *parse_array(const char **json) {
    skip_whitespace(json);
    if (**json == '[') {
        (*json)++;
        skip_whitespace(json);
        JsonValue *array_value = (JsonValue *) malloc(sizeof(JsonValue));
        array_value->type = JSON_ARRAY;
        array_value->value.array.count = 0;
        array_value->value.array.values = NULL;
        while (**json != ']' && **json != '\0') {
            JsonValue *element = parse_json(json);
            if (element) {
                array_value->value.array.count++;
                array_value->value.array.values = (JsonValue *) realloc(array_value->value.array.values,
                    array_value->value.array.count * sizeof(JsonValue));
                array_value->value.array.values[array_value->value.array.count - 1] = *element;
                free(element);
            } else {
                break;
            }
            skip_whitespace(json);
            if (**json == ',') {
                (*json)++;
            }
        }
        if (**json == ']') {
            (*json)++;
            return array_value;
        } else {
            free_json_value(array_value);
            return NULL;
        }
    }
    return NULL;
}

static JsonValue *parse_object(const char **json) {
    skip_whitespace(json);
    if (**json == '{') {
        (*json)++;
        skip_whitespace(json);
        JsonValue *object_value = (JsonValue *) malloc(sizeof(JsonValue));
        object_value->type = JSON_OBJECT;
        object_value->value.object.count = 0;
        object_value->value.object.keys = NULL;
        object_value->value.object.values = NULL;
        while (**json != '}' && **json != '\0') {
            JsonValue *key = parse_string(json);
            if (key) {
                skip_whitespace(json);
                if (**json == ':') {
                    (*json)++;
                    JsonValue *value = parse_json(json);
                    if (value) {
                        object_value->value.object.count++;
                        object_value->value.object.keys = (char **) realloc(object_value->value.object.keys,
                            object_value->value.object.count * sizeof(char *));
                        object_value->value.object.keys[object_value->value.object.count - 1] = key->value.string;
                        object_value->value.object.values = (JsonValue *) realloc(object_value->value.object.values,
                            object_value->value.object.count * sizeof(JsonValue));
                        object_value->value.object.values[object_value->value.object.count - 1] = *value;
                        free(value);
                    } else {
                        free_json_value(key);
                        break;
                    }
                } else {
                    free_json_value(key);
                    break;
                }
            } else {
                break;
            }
            skip_whitespace(json);
            if (**json == ',') {
                (*json)++;
            }
        }
        if (**json == '}') {
            (*json)++;
            return object_value;
        } else {
            free_json_value(object_value);
            return NULL;
        }
    }
    return NULL;
}

/* Hàm phân tích cú pháp JSON công khai */
JsonValue *parse_json(const char **json) { 
    while (isspace(**json)) {
        (*json)++;
    }
    switch (**json) {
        case 'n':
            return parse_null(json);
        case 't':
        case 'f':
            return parse_boolean(json);
        case '\"':
            return parse_string(json);
        case '[':
            return parse_array(json);
        case '{':
            return parse_object(json);
        default:
            if (isdigit(**json) || **json == '-') {
                return parse_number(json);
            } else {
                /* Lỗi phân tích cú pháp */
                return NULL;
            }
    }
}

/* Hàm giải phóng bộ nhớ đã cấp phát cho JSON */
void free_json_value(JsonValue *json_value) {
    if (json_value == NULL) {
        return;
    }
    switch (json_value->type) {
        case JSON_STRING:
            free(json_value->value.string);
            break;
        case JSON_ARRAY:
            for (size_t i = 0; i < json_value->value.array.count; i++) {
                free_json_value(&json_value->value.array.values[i]);
            }
            free(json_value->value.array.values);
            break;
        case JSON_OBJECT:
            for (size_t i = 0; i < json_value->value.object.count; i++) {
                free(json_value->value.object.keys[i]);
                free_json_value(&json_value->value.object.values[i]);
            }
            free(json_value->value.object.keys);
            free(json_value->value.object.values);
            break;
        default:
            break;
    }
    free(json_value);
}

/* Hàm hiển thị nội dung JSON dạng đệ quy */
void test(JsonValue *json_value) {
    if (json_value != NULL && json_value->type == JSON_OBJECT) {
        size_t num_fields = json_value->value.object.count;
        for (size_t i = 0; i < num_fields; ++i) {
            char *key = json_value->value.object.keys[i];
            JsonValue *value = &json_value->value.object.values[i];
            JsonType type = value->type;
            if (type == JSON_STRING) {
                printf("%s: %s\n", key, value->value.string);
            }
            if (type == JSON_NUMBER) {
                printf("%s: %f\n", key, value->value.number);
            }
            if (type == JSON_BOOLEAN) {
                printf("%s: %s\n", key, value->value.boolean ? "True" : "False");
            }
            if (type == JSON_OBJECT) {
                printf("%s:\n", key);
                test(value);
            }
            if (type == JSON_ARRAY) {
                printf("%s: ", key);
                for (size_t j = 0; j < value->value.array.count; j++) {
                    test(&value->value.array.values[j]);
                }
                printf("\n");
            }
        }
    } else {
        if (json_value->type == JSON_STRING) {
            printf("%s ", json_value->value.string);
        }
        if (json_value->type == JSON_NUMBER) {
            printf("%f ", json_value->value.number);
        }
        if (json_value->type == JSON_BOOLEAN) {
            printf("%s ", json_value->value.boolean ? "True" : "False");
        }
        if (json_value->type == JSON_OBJECT) {
            printf("%s:\n", json_value->value.object.keys);
            test(json_value->value.object.values);
        }
    }
}
