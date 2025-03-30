#ifndef PARSE_JSON_H
#define PARSE_JSON_H

#include <stddef.h>
#include <stdbool.h>

typedef enum {
    JSON_NULL,
    JSON_BOOLEAN,
    JSON_NUMBER,
    JSON_STRING,
    JSON_ARRAY,
    JSON_OBJECT
} JsonType;

typedef struct JsonValue {
    JsonType type;
    union {
        int boolean;
        double number;
        char *string;
        struct {
            struct JsonValue *values;
            size_t count;
        } array;
        struct {
            char **keys;
            struct JsonValue *values;
            size_t count;
        } object;
    } value;
} JsonValue;

/* Các hàm public */
JsonValue *parse_json(const char **json);
void free_json_value(JsonValue *json_value);
void test(JsonValue *json_value);

#endif // PARSE_JSON_H
