# ADVANCED-C-CPP
#  BAI 1 COMPILER PROCESS - MACRO
<details>
  <summary>Chi tiết</summary>
 
## 1. Tiền Xử Lý (Preprocessing)
Quá trình tiền xử lý chuyển đổi file `.c` hoặc `.h` thành file `.i`. Lệnh biên dịch:
```sh
gcc -E main.c -o main.i
```
### Các bước trong tiền xử lý:
- **Copy toàn bộ mã nguồn** của các thư viện hoặc file được `#include`.
- **Xóa toàn bộ chú thích** (`//` và `/* ... */`).
- **Thay thế các macro** được định nghĩa bởi `#define`.
- **Giữ nguyên các hàm và biến thông thường**.

Lệnh kiểm tra file `.i` sau tiền xử lý:
```sh
cat main.i
```

### Ví dụ về Macro trong Tiền Xử Lý
#### 1. `#define` - Định nghĩa hằng số
```c
#include <stdio.h>
#define PI 3.14159
int main() {
    printf("PI = %f\n", PI);
    return 0;
}
```
*Kết quả khi chạy chương trình:*
```
PI = 3.141590
```

#### 2. `#define` - Định nghĩa hàm macro
```c
#include <stdio.h>
#define SQUARE(x) ((x) * (x))
int main() {
    printf("Bình phương của 5 là: %d\n", SQUARE(5));
    return 0;
}
```
*Kết quả:*
```
Bình phương của 5 là: 25
```

#### 3. `#undef` - Hủy định nghĩa macro
```c
#include <stdio.h>
#define VALUE 100
#undef VALUE
int main() {
    #ifdef VALUE
        printf("VALUE is defined\n");
    #else
        printf("VALUE is not defined\n");
    #endif
    return 0;
}
```
*Kết quả:*
```
VALUE is not defined
```

#### 4. `##` - Nối chuỗi
```c
#include <stdio.h>
#define CONCAT(a, b) a##b
int main() {
    int xy = 10;
    printf("%d\n", CONCAT(x, y));
    return 0;
}
```
*Kết quả:*
```
10
```

#### 5. `#` - Chuyển văn bản thành chuỗi
```c
#include <stdio.h>
#define TO_STRING(x) #x
int main() {
    printf("%s\n", TO_STRING(Hello World));
    return 0;
}
```
*Kết quả:*
```
Hello World
```

#### 6. `...` (Variadic Macro) - Macro nhận nhiều tham số
```c
#define sum(...)                \
int arr[] = {__VA_ARGS__, 0};   \
int i =0;                       \
int tong = 0;                   \
while (arr[i] != 0 )            \
{                               \
    tong += arr[i];             \         
    i++;                        \
}                               \   
printf("tong bang: %d", tong) ; \  

*Kết quả:*
Tổng: 15
```

---

## 2. Biên Dịch (Compilation)
Quá trình biên dịch chuyển đổi file `.i` thành file `.s` (hợp ngữ - assembly).

Lệnh biên dịch:
```sh
gcc -S main.i -o main.s
```
Lệnh kiểm tra file `.s`:
```sh
cat main.s
```

---

## 3. Dịch Assembly (Assembler)
Quá trình assembler chuyển đổi file `.s` thành file `.o` (mã máy).

Lệnh dịch assembly:
```sh
gcc -c main.s -o main.o
```
Lệnh kiểm tra file `.o` (dạng nhị phân, không đọc được trực tiếp):
```sh
ls -l main.o
```

---

## 4. Liên Kết (Linking)
Quá trình linker kết hợp các file `.o` để tạo ra file thực thi `.exe`.

Lệnh liên kết:
```sh
gcc main.o -o main.exe
```
Lệnh chạy file thực thi:
```sh
./main.exe
```

---

## 5. Tóm Tắt Quá Trình Biên Dịch

```
file.c hoặc file.h  →  (Preprocessing)  →  file.i  →  (Compilation)  →  file.s  →  (Assembler)  →  file.o  →  (Linker)  →  file.exe
```

Từng bước với lệnh cụ thể:
1. **Tiền xử lý:** `gcc -E main.c -o main.i`
2. **Biên dịch:** `gcc -S main.i -o main.s`
3. **Dịch assembly:** `gcc -c main.s -o main.o`
4. **Liên kết:** `gcc main.o -o main.exe`
5. **Chạy chương trình:** `./main.exe`

Mỗi bước trên đều có thể kiểm tra bằng cách xem nội dung file tương ứng (`cat`, `ls -l`).
  </details>

# BAI 2 STDARG - ASSERT
<details>
  <summary>Chi tiết</summary>
  
## 1. Thư viện stdarg.h

### 1.1 Mục đích
- Hỗ trợ xây dựng các hàm có số lượng tham số biến đổi (variadic functions).
- Cho phép truy cập vào danh sách các đối số được truyền vào sau đối số cố định cuối cùng.

### 1.2 Các macro chính
- **`va_list`**  
  Kiểu dữ liệu dùng để lưu trữ danh sách tham số biến đổi.

- **`va_start(va_list, last_fixed_arg)`**  
  Khởi tạo danh sách các đối số biến đổi, trong đó `last_fixed_arg` là đối số cuối cùng có kiểu cố định.

- **`va_arg(va_list, type)`**  
  Lấy đối số tiếp theo từ danh sách với kiểu dữ liệu được chỉ định.

- **`va_end(va_list)`**  
  Giải phóng tài nguyên được cấp phát cho danh sách các đối số.

### 1.3 Ví dụ sử dụng stdarg.h

Ví dụ: Hàm `sum` tính tổng các số nguyên cho đến khi gặp một sentinel.  
Trong ví dụ này, sử dụng sentinel `'a'` để đánh dấu điểm kết thúc danh sách.

```c
#include <stdio.h>
#include <stdarg.h>

#define tong(...) sum(__VA_ARGS__, 'a') // 'a' làm sentinel

int sum(int first, ...) {
    va_list args;
    va_start(args, first);
    
    // Lưu các số vào mảng tạm (giả sử không vượt quá 100 giá trị)
    int numbers[100];
    int count = 0;
    
    numbers[count++] = first;
    
    // Đọc các đối số cho đến khi gặp sentinel
    while (1) {
        int value = va_arg(args, int);
        // Ép về char để so sánh với sentinel 'a'
        if ((char)value == 'a') {
            break;
        }
        numbers[count++] = value;
    }
    
    va_end(args);
    
    int result = 0;
    for (int i = 0; i < count; i++) {
        result += numbers[i];
    }
    
    return result;
}

int main() {
    
    printf("Tong cac gia tri: %d\n", tong(4, 9, 0, 10, 15, 20));
    return 0;
}
```

## 2. Tổng quan về assert.h
- **assert.h** là thư viện tiêu chuẩn trong C cung cấp macro `assert`.
- Macro `assert(condition)` được sử dụng để kiểm tra điều kiện tại thời điểm chạy (runtime). Nếu điều kiện không được thỏa mãn (false), chương trình sẽ dừng lại và in ra thông báo lỗi, kèm theo thông tin về file và số dòng.

### 2.1. Cách thức hoạt động của assert
- Khi biểu thức trong `assert(condition)` được đánh giá là false (0), chương trình:
  - In ra thông báo lỗi, bao gồm tên file, số dòng và nội dung biểu thức không thỏa mãn.
  - Gọi hàm `abort()` để kết thúc chương trình ngay lập tức.
- Nếu biểu thức đúng (non-zero), `assert` không thực hiện hành động nào và chương trình tiếp tục chạy bình thường.

### 2.2. Ví dụ sử dụng assert
Dưới đây là một ví dụ minh họa cách sử dụng `assert` để đảm bảo rằng một giá trị không bị chia cho số 0:

```c
#include <stdio.h>
#include <assert.h>

// Hàm chia, kiểm tra điều kiện không chia cho 0
int divide(int a, int b) {
    // Kiểm tra rằng b không bằng 0
    assert(b != 0);
    return a / b;
}

int main() {
    int x = 10;
    int y = 0;  // Thử nghiệm với giá trị 0 để kích hoạt assert
    // Nếu y bằng 0, assert sẽ dừng chương trình và thông báo lỗi
    int result = divide(x, y);
    printf("Result: %d\n", result);
    return 0;
}
```
  </details>

# BAI 3 BITMARK

<details>
  <summary>Chi tiết</summary>

## 1. Giới thiệu về Bitmask
Bitmask là một kỹ thuật sử dụng các bit để lưu trữ và thao tác với các cờ (flags) hoặc trạng thái trong một biến số nguyên. Kỹ thuật này giúp tối ưu hóa bộ nhớ, thực hiện các phép toán logic trên một cụm bit, và quản lý các trạng thái, quyền truy cập, hoặc các thuộc tính khác của một đối tượng.

## 2. Các Toán Tử Bitwise
Toán tử bitwise được sử dụng để thao tác trực tiếp trên các bit của một số. Dưới đây là danh sách các toán tử bitwise cơ bản:

### 2.1. Phép NOT (~)
- Đảo ngược tất cả các bit của số.
- Bit 1 sẽ thành 0, bit 0 sẽ thành 1.

Ví dụ:
```cpp
#include <stdio.h>
#include <stdint.h>

int main() {
    uint8_t user1 = 0b00001110;
    uint8_t user2 = 0b10101001;
    printf("~user1 = 0b%08b\n", (uint8_t)~user1);
    printf("~user2 = 0b%08b\n", (uint8_t)~user2);
    return 0;
}
```

Kết quả:
```
~user1 = 0b11110001
~user2 = 0b01010110
```

### 2.2. Phép AND (&)
- Chỉ trả về 1 nếu cả hai bit đều là 1.

Ví dụ:
```cpp
user1 & user2 // Kết quả: 0b00001000
```

### 2.3. Phép OR (|)
- Trả về 1 nếu ít nhất một trong hai bit là 1.

Ví dụ:
```cpp
user1 | user2 // Kết quả: 0b10101111
```

### 2.4. Phép XOR (^)
- Trả về 1 nếu hai bit khác nhau, ngược lại trả về 0.

Ví dụ:
```cpp
user1 ^ user2 // Kết quả: 0b10100111
```

### 2.5. Phép Dịch Bit (>> và <<)
- `>>`: Dịch phải, các bit bên trái bị đẩy ra ngoài, các bit mới bên phải được lấp bằng 0 hoặc 1 (tùy vào số âm hay dương).
- `<<`: Dịch trái, các bit bên phải bị đẩy ra ngoài, các bit mới bên trái được lấp bằng 0.

Ví dụ:
```cpp
// Dịch phải
user1 >> 1 // Kết quả: 0b00000111
user1 >> 5 // Kết quả: 0b00000000

// Dịch trái
user2 << 6 // Kết quả: 0b10000000
```

## 3. Ứng Dụng Bitmask
### 3.1. Kiểm tra trạng thái bit
```cpp
if (user1 & (1 << 3)) {
    printf("Bit thứ 3 đang bật\n");
}
```

### 3.2. Bật một bit cụ thể
```cpp
user1 |= (1 << 2); // Bật bit thứ 2
```

### 3.3. Tắt một bit cụ thể
```cpp
user1 &= ~(1 << 2); // Tắt bit thứ 2
```

### 3.4. Đảo trạng thái một bit
```cpp
user1 ^= (1 << 2); // Đảo bit thứ 2
```

## 4. Sử dụng Bit-Field trong C
Bit-field là một cách tối ưu hóa bộ nhớ bằng cách định nghĩa các trường bit trong struct.

Ví dụ:
```cpp
#include <stdio.h>

struct Status {
    unsigned int bit0 : 1;
    unsigned int bit1 : 1;
    unsigned int bit2 : 1;
    unsigned int bit3 : 1;
};

int main() {
    struct Status status = {1, 0, 1, 1};
    printf("Bit 0: %d, Bit 1: %d, Bit 2: %d, Bit 3: %d\n",
           status.bit0, status.bit1, status.bit2, status.bit3);
    return 0;
}
```

## 5. Kết luận
Bitmask là một kỹ thuật hữu ích giúp tối ưu hóa bộ nhớ và xử lý dữ liệu hiệu quả trong lập trình hệ thống và nhúng. Việc sử dụng các toán tử bitwise giúp quản lý trạng thái và quyền truy cập một cách nhanh chóng và tiết kiệm bộ nhớ.
</details>

# BAI 4 POINTER

<details>
  <summary>Chi tiết</summary>

## 1. Tổng quan về Pointer

- **Khái niệm**: Con trỏ (pointer) là một biến đặc biệt trong ngôn ngữ lập trình C, chứa địa chỉ bộ nhớ của một đối tượng khác như biến, hàm, hoặc mảng. Việc sử dụng con trỏ giúp chúng ta thực hiện các thao tác trên bộ nhớ một cách linh hoạt và hiệu quả hơn.

- **Cách khai báo**: Con trỏ được khai báo bằng cách sử dụng dấu `*` trước tên biến:
```c
int *ptr;       // Con trỏ đến kiểu int
char *ptr_char; // Con trỏ đến kiểu char
float *ptr_float; // Con trỏ đến kiểu float
```

- **Lấy địa chỉ của một biến**: Để lấy địa chỉ của một biến, sử dụng toán tử `&`:
```c
int x = 10;
int *ptr_x = &x;  // ptr_x giờ đây chứa địa chỉ của x
```

- **Truy cập giá trị thông qua con trỏ**: Để truy cập giá trị của biến mà con trỏ trỏ tới, sử dụng toán tử `*` (dereference) giải tham chiếu:
```c
int y = *ptr_x;  // y sẽ bằng giá trị của x
```

- **Kích thước của con trỏ**: Kích thước của con trỏ phụ thuộc vào kiến trúc máy tính và trình biên dịch hoặc kiến trúc vi điều khiển. Sử dụng `sizeof()` để kiểm tra kích thước của con trỏ:
```c
#include <stdio.h>

int main() {
    int *ptr;
    printf("Size of pointer: %d bytes\n", sizeof(ptr));
    return 0;
}
```

- **Ví dụ minh họa**
Ví dụ về các nội dung trên.
```c
#include <stdio.h>

int main() {
    int test = 5;   // address: 0x01
                    // value:   5
    int *ptr = &test;  // address: 0xf1
                       // value: 0x01

    printf("Địa chỉ của con trỏ: %p\n", ptr);// Lấy giá trị địa chỉ con trỏ
    printf("Địa chỉ mà con trỏ đang trỏ tới: %p\n", &ptr); // Lấy địa chỉ mà con trỏ đang trỏ tới
    printf("Giá trị tại địa chỉ con trỏ đang trỏ tới: %d\n", *ptr); // Lấy giá trị tại địa chỉ con trỏ đang trỏ tới

    return 0;
}
```

- **Con trỏ và mảng**: Đối với một mảng, địa chỉ mà con trỏ trỏ đến là vị trí phần tử đầu tiên trong mảng. Khi khai báo, ta chỉ cần gán tên mảng cho con trỏ:
```c
#include <stdio.h>

int main() {
    uint16_t arr[] = {5, 8, 7};
    uint16_t *ptr = arr;  // giá trị ptr = &arr[0] = 0xa0; *ptr = arr[0] = 5;
                          // (ptr + 1) = &arr[1] = 0xa2;   *(ptr + 1) = arr[1] = 8;

    printf("Giá trị phần tử đầu tiên: %d\n", *ptr);
    printf("Giá trị phần tử thứ hai: %d\n", *(ptr + 1));
    printf("Giá trị phần tử thứ ba: %d\n", *(ptr + 2));

    return 0;
}
```

- **Kích thước con trỏ**: Kích thước của con trỏ phụ thuộc vào kiến trúc máy tính. Trên hệ thống 32-bit, kích thước con trỏ thường là 4 byte, trong khi trên hệ thống 64-bit, kích thước con trỏ thường là 8 byte.

- **Mục đích của dữ liệu khai báo cho con trỏ**: Dữ liệu khai báo cho con trỏ phục vụ vào mục đích đọc dữ liệu tại vị trí mà con trỏ đang trỏ đến. Điều này giúp đảm bảo rằng con trỏ được sử dụng đúng cách và tránh các lỗi truy cập bộ nhớ.

## 2. Void Pointer

- **Void Pointer**: Con trỏ void (void pointer) là một con trỏ có thể trỏ tới bất kỳ kiểu dữ liệu nào. Điều này có nghĩa là con trỏ void không có kiểu dữ liệu cụ thể, và do đó, nó có thể được sử dụng để trỏ tới bất kỳ địa chỉ bộ nhớ nào mà không cần biết trước kiểu dữ liệu của giá trị tại địa chỉ đó.

- **Khai báo**: Con trỏ void được khai báo bằng cách sử dụng từ khóa `void` trước dấu `*`.
  ```c
  void *ptr_void;
  ```

- **Đặc điểm**:
    - Con trỏ void có thể trỏ tới bất kỳ kiểu dữ liệu nào, giúp nó rất linh hoạt trong việc quản lý bộ nhớ và xử lý dữ liệu.
    - Không thể truy cập trực tiếp giá trị mà con trỏ void trỏ tới mà không chuyển đổi nó sang kiểu dữ liệu cụ thể.

- **Ví dụ sử dụng con trỏ void**
```c
#include <stdio.h>

int main(int argc, char const *argv[]) {
    void *ptr_void;
    int a = 5;
    ptr_void = &a;
    printf("Địa chỉ: %p \n Địa chỉ: %d \n Giá trị: %d\n", ptr_void, ptr_void, *(int*)ptr_void); // ép kiểu dữ liệu về int
  
    double b = 3.14;
    ptr_void = &b;
    printf("Địa chỉ: %p \n Địa chỉ: %d \n Giá trị: %0.2f", ptr_void, ptr_void, *(double*)ptr_void); // ép kiểu dữ liệu về double
    
    char c = 'c';
    ptr_void = &c;
    printf("\nĐịa chỉ: %p\n Địa chỉ: %d \n Giá trị: %c ", ptr_void, ptr_void, *(char*)ptr_void); // ép kiểu dữ liệu về char
    
    char arr[] = "hello ho bao ton";
    ptr_void = arr; // vị trí pointer trỏ đến vị trí phần tử đầu tiên trong mảng
    for (int i = 0; i < sizeof(arr); i++) {
        ptr_void = &arr[i];
        printf("\nGiá trị: %c", *(char*)(ptr_void + 1));
    }

    void *ptr1[] = {&a, &b, &c, arr}; // mảng con trỏ với giá trị là địa chỉ các đối tượng
    printf("ptr1[0] = %d\n", *(int*)ptr1[0]);
    printf("ptr1[1] = %f\n", *(double*)ptr1[1]);
    printf("ptr1[2] = %c\n", *(char*)ptr1[2]);
    for (int i = 0; i < sizeof(arr); i++) {
        printf("ptr1[%d] = %c\n", i, *(char*)(ptr1[3] + i)); 
        printf("ptr1[%d] = %p\n", i, (ptr1[3] + i));   
    }
    return 0;
}
```

- **Ứng dụng của con trỏ void**
    - **Quản lý bộ nhớ động**: Con trỏ void thường được sử dụng trong các hàm quản lý bộ nhớ động như `malloc`, `calloc`, và `realloc` để trả về địa chỉ của vùng nhớ được cấp phát mà không cần biết trước kiểu dữ liệu.
    EX: 
    ```c
        int *a;
        a = (int*)malloc(sizeof(int) * n);
    ```
    - **Hàm tổng quát**: Con trỏ void có thể được sử dụng trong các hàm tổng quát để xử lý các kiểu dữ liệu khác nhau mà không cần viết lại mã cho từng kiểu dữ liệu cụ thể.

## 3. Function Pointer

- **Con Trỏ Hàm**:Con trỏ hàm là một biến lưu trữ địa chỉ của một hàm. Cho phép gọi hàm thông qua con trỏ, truyền hàm như là một đối số cho một hàm khác, hoặc lưu trữ địa chỉ của hàm trong một cấu trúc dữ liệu. 

- **Khai báo con trỏ hàm**: Con trỏ hàm phải có cùng kiểu dữ liệu trả về và cùng kiểu dữ liệu tham số với hàm mà nó trỏ tới.
  ```c
  void (*ptr)(int, int);
  ```

- **Ví dụ về con trỏ hàm**: 
```c
#include <stdio.h>

// Hàm cộng hai số nguyên
void sum(int a, int b) {
    printf("%d + %d = %d\n", a, b, a + b);
}

// Hàm trừ hai số nguyên
void subtract(int a, int b) {
    printf("%d - %d = %d\n", a, b, a - b);
}

// Hàm tính toán, nhận con trỏ hàm làm tham số
void calculator(void (*ptr)(int, int), int a, int b) {
    ptr(a, b);
}

int main(int argc, char const *argv[]) {
    // Khai báo và gán con trỏ hàm
    void (*ptr)(int, int) = sum; // Con trỏ hàm trỏ tới hàm sum
    ptr(2, 3); // Gọi hàm sum thông qua con trỏ hàm

    void (*ptr1)(int, int) = &subtract; // Con trỏ hàm trỏ tới hàm subtract
    ptr1(10, 3); // Gọi hàm subtract thông qua con trỏ hàm

    // In địa chỉ của hàm subtract
    printf("%p\n", *ptr1);
    printf("%p\n", ptr1);
    printf("%p\n", &subtract);

    // Mảng con trỏ hàm
    void (*fptr[])(int, int) = {sum, subtract};
    fptr[0](5, 25); // Gọi hàm sum thông qua mảng con trỏ hàm
    fptr[1](36, 7); // Gọi hàm subtract thông qua mảng con trỏ hàm

    // Truyền con trỏ hàm trực tiếp vào hàm calculator
    calculator(sum, 9, 15);
    calculator(subtract, 9, 15);

    return 0;
}
```
- **Giải thích**
    - **Khai báo con trỏ hàm**:
   ```c
   void (*ptr)(int, int) = sum;
   ```
   Con trỏ hàm `ptr` được khai báo để trỏ tới hàm `sum`. Con trỏ hàm phải có cùng kiểu dữ liệu trả về và cùng kiểu dữ liệu tham số với hàm mà nó trỏ tới.

    - **Gọi hàm thông qua con trỏ hàm**:
   ```c
   ptr(2, 3);
   ```
   Gọi hàm `sum` thông qua con trỏ hàm `ptr`.

    - **Mảng con trỏ hàm**:
   ```c
   void (*fptr[])(int, int) = {sum, subtract};
   ```
   Khai báo một mảng con trỏ hàm `fptr` chứa địa chỉ của các hàm `sum` và `subtract`.

    - **Truyền con trỏ hàm vào hàm khác**:
   ```c
   calculator(sum, 9, 15);
   ```
   Truyền con trỏ hàm `sum` trực tiếp vào hàm `calculator`.

## 4. Pointer to Constant

- **Pointer to Constant (con trỏ hằng)**: Con trỏ hẳng (pointer to constant) là một con trỏ mà giá trị tại địa chỉ nó trỏ tới không thể thay đổi thông qua con trỏ. Tuy nhiên, địa chỉ mà hằng con trỏ trỏ tới có thể thay đổi. Điều này có nghĩa là bạn có thể thay đổi địa chỉ mà con trỏ trỏ tới, nhưng không thể thay đổi giá trị tại địa chỉ đó thông qua con trỏ. (chỉ cho phép đọc giá trị tại vị trí trỏ tới không cho phép thay đổi giá trị)

- **Khai báo con trỏ hằng**: Con trỏ hằng được khai báo bằng cách sử dụng từ khóa `const` trước kiểu dữ liệu của con trỏ.
  ```c
  const int *ptr;
  hoặc int const *ptr;
  ```

- **Ví dụ về hằng con trỏ**
```c
#include <stdio.h>

int main() {
    int value1 = 10;
    int value2 = 20;
    const int *ptr = &value1; // Con trỏ hằng trỏ tới biến value1

    printf("Giá trị của value1: %d\n", *ptr);

    // Thử thay đổi giá trị tại địa chỉ mà hằng con trỏ trỏ tới (sẽ gây lỗi)
    // *ptr = 15; // Lỗi: không thể thay đổi giá trị thông qua hằng con trỏ
    // muốn thay đối giá trị phải thay đổi trực tiếp trên biến gốc
    // Thay đổi địa chỉ mà hằng con trỏ trỏ tới
    ptr = &value2;
    printf("Giá trị của value2: %d\n", *ptr);

    return 0;
}
```

## 5 Constant to Pointer

- **Hằng con trỏ**: Hằng con trỏ (constant pointer) là một con trỏ mà địa chỉ nó trỏ tới không thể thay đổi sau khi được khởi tạo. Điều này có nghĩa là khi hằng con trỏ được khởi tạo, nó sẽ luôn trỏ tới một địa chỉ bộ nhớ và không thể trỏ tới địa chỉ khác. Tuy nhiên, giá trị tại địa chỉ mà hằng con trỏ trỏ tới có thể thay đổi. 

- **Khai báo hằng con trỏ**: hằng con trỏ được khai báo bằng cách sử dụng từ khóa `const` trước kiểu dữ liệu của con trỏ.
  ```c
  int *const ptr;
  ```

- **Ví dụ về hằng con trỏ**
```c
#include <stdio.h>

int a = 5;
int b = 10;
int const *ptr = &a; // Con trỏ hằng trỏ tới biến a
int *ptr1 = &a;
const char *st1 = "hello";
const char *st2 = "world";

int *const cptr = &b; // Hằng con trỏ trỏ tới biến b

int main(int argc, char const *argv[]) {
    *ptr1 = 15;
    printf("%p\n%d\n", ptr, *ptr);
    ptr = &b;
    printf("%p\n%d\n", ptr, *ptr);

    printf("%p\n%d\n", cptr, *cptr);
    return 0;
    // cptr = &a; // Lỗi: không thể thay đổi địa chỉ của con trỏ hằng
    // printf("%p\n%d\n", cptr, *cptr);
}
```

- **Giải thích chi tiết**
    **Khai báo hằng con trỏ**:
   ```c
   int *const cptr = &b;
   ```
   Con trỏ `cptr` được khai báo là hằng con trỏ trỏ tới biến `b`. Điều này có nghĩa là `cptr` không thể trỏ tới địa chỉ khác sau khi được khởi tạo.

    **Thay đổi giá trị tại địa chỉ mà hằng con trỏ trỏ tới**:
   ```c
   *ptr1 = 15;
   ```
   Giá trị tại địa chỉ mà con trỏ `ptr1` trỏ tới có thể thay đổi, nhưng địa chỉ mà con trỏ `cptr` trỏ tới không thể thay đổi.

## 6. Null Pointer

- **Null Pointer**: Null pointer (con trỏ null) là một con trỏ không trỏ tới bất kỳ địa chỉ nào trong bộ nhớ. Nó thường được sử dụng để chỉ ra rằng con trỏ không được khởi tạo hoặc không trỏ tới bất kỳ đối tượng nào. 

- **Khai báo null pointer**: Null pointer được khai báo bằng cách gán giá trị `NULL` cho con trỏ.
  ```c
  int *ptr = NULL;
  ```

- **Ví dụ về null pointer**
```c
#include <stdio.h>

int main() {
    int *ptr = NULL; // Khai báo con trỏ null

    if (ptr == NULL) {
        printf("Con trỏ ptr không trỏ tới bất kỳ địa chỉ hợp lệ nào.\n");
    }

    // Thử truy cập giá trị tại địa chỉ mà con trỏ null trỏ tới (sẽ gây lỗi)
    // printf("%d\n", *ptr); // Lỗi: không thể dereference con trỏ null

    return 0;
}
```
## 7. Pointer to Pointer

- **Con Trỏ Trỏ Tới Con Trỏ (pointer to pointer)**:Con trỏ trỏ tới con trỏ (pointer to pointer) là một con trỏ mà giá trị của nó là địa chỉ của một con trỏ khác. Cho phép tạo ra các cấp độ con trỏ khác nhau, giúp quản lý và thao tác với các con trỏ một cách linh hoạt hơn.

- **Khai báo con trỏ trỏ tới con trỏ**: Con trỏ trỏ tới con trỏ được khai báo bằng cách sử dụng hai dấu `*` trước tên biến.
  ```c
  int **ptr;
  ```

- **Ví dụ về con trỏ trỏ tới con trỏ**
```c
#include <stdio.h>

int main() {
    int value = 10;
    int *ptr = &value;  // Con trỏ trỏ tới biến value
    int **ptr_to_ptr = &ptr;  // Con trỏ trỏ tới con trỏ ptr

    // In giá trị của biến value thông qua con trỏ ptr
    printf("Giá trị của value: %d\n", *ptr);

    // In giá trị của biến value thông qua con trỏ trỏ tới con trỏ ptr_to_ptr
    printf("Giá trị của value thông qua con trỏ trỏ tới con trỏ: %d\n", **ptr_to_ptr);

    // In địa chỉ của biến value
    printf("Địa chỉ của value: %p\n", (void*)&value);

    // In địa chỉ mà con trỏ ptr trỏ tới (địa chỉ của biến value)
    printf("Địa chỉ mà con trỏ ptr trỏ tới: %p\n", (void*)ptr);

    // In địa chỉ của con trỏ ptr
    printf("Địa chỉ của con trỏ ptr: %p\n", (void*)&ptr);

    // In địa chỉ mà con trỏ trỏ tới con trỏ ptr_to_ptr trỏ tới (địa chỉ của con trỏ ptr)
    printf("Địa chỉ mà con trỏ trỏ tới con trỏ ptr_to_ptr trỏ tới: %p\n", (void*)ptr_to_ptr);

    return 0;
}
```
</details>

# BÀI 5 STORAGR CLASS (Extern- Static- Volatile- Register)

<details>
  <summary>Chi tiết</summary>

## 1. Extern 
### 1.1.Khai báo biến `extern`**:
   ```c
   // File1.c
   int a = 10; // Định nghĩa biến a

   // File2.c
   extern int a; // Khai báo biến a
   ```

### 1.2. Khai báo hàm `extern`**:
   ```c
   // File1.c
   void display() {
       printf("Hello, World!\n");
   }

   // File2.c
   extern void display(); // Khai báo hàm display
   ```

### 1.3. Lưu ý khi sử dụng `extern`
- **Không định nghĩa lại**: Khi sử dụng `extern`, chỉ khai báo biến hoặc hàm mà không định nghĩa lại chúng.
- **Chỉ sử dụng cho biến toàn cục**
- **Liên kết các tệp**: Các tệp chứa khai báo `extern` và định nghĩa thực tế phải được liên kết với nhau khi biên dịch. Ví dụ:
```bash
  gcc File1.c File2.c -o output
  ```

### 1.4. Ứng dụng của `extern`
- **Chia sẻ biến và hàm giữa các tệp**: `extern` cho phép chia sẻ các biến và hàm giữa các tệp khác nhau trong cùng một dự án.
- **Thiết kế thư viện**: `extern` thường được sử dụng trong thiết kế thư viện để khai báo các hàm và biến mà thư viện cung cấp.

### 1.5. Ví dụ chi tiết
Giả sử có hai tệp nguồn: `main.c` và `utils.c`.

**main.c**:
```c
#include <stdio.h>

// Khai báo biến extern
extern int count;

// Khai báo hàm extern
extern void increment();

int main() {
    count = 0;
    increment();
    printf("Count: %d\n", count);
    return 0;
}
```

**utils.c**:
```c
#include <stdio.h>

// Định nghĩa biến
int count;

// Định nghĩa hàm
void increment() {
    count++;
}
```

Khi biên dịch, cần liên kết cả hai tệp lại với nhau:
```bash
gcc main.c utils.c -o program
```

Khi chạy gõ lệnh `./program` trong TERMINAL

Kết quả khi chạy chương trình `program` sẽ là:
```
Count: 1
```

## 2. Static

### 2.1. Static local variables

#### 2.1.1 Đặc điểm của biến cục bộ tĩnh
- **Thời gian hoạt động**: Khác với các biến cục bộ thông thường, biến cục bộ tĩnh được tạo ra chỉ một lần và giữ nguyên giá trị của nó giữa các lần gọi hàm. Điều này có nghĩa là giá trị của biến sẽ được bảo toàn ngay cả khi hàm kết thúc và được gọi lại sau đó.
- **Phạm vi**: Biến cục bộ tĩnh chỉ có thể truy cập được trong phạm vi của hàm nơi nó được khai báo, giống như các biến cục bộ thông thường.
- **Khởi tạo**: Biến cục bộ tĩnh chỉ được khởi tạo một lần, lần đầu tiên hàm được gọi. Nếu không được khởi tạo cụ thể, chúng sẽ tự động được khởi tạo với giá trị 0.

#### 2.1.2. Ví dụ
Dưới đây là một ví dụ minh họa về cách biến cục bộ tĩnh hoạt động:

```c
#include <stdio.h>

void countCalls() {
    static int count = 0; // Biến cục bộ tĩnh
    count++;
    printf("Hàm được gọi %d lần\n", count);
}

int main() {
    countCalls(); // Output: Hàm được gọi 1 lần kq = 1
    countCalls(); // Output: Hàm được gọi 2 lần kq = 2
    countCalls(); // Output: Hàm được gọi 3 lần kq = 3
    return 0;
}
```

Trong ví dụ trên, biến `count` là một biến cục bộ tĩnh được khai báo trong hàm `countCalls`. Nó giữ nguyên giá trị của mình giữa các lần gọi hàm, do đó mỗi lần hàm được gọi, giá trị của `count` sẽ tăng lên.

#### 2.1.3. Lưu trữ trong bộ nhớ
- **Biến cục bộ tĩnh** được lưu trữ trong phân vùng dữ liệu (data segment) của bộ nhớ, không phải trong stack. Do đó thời gian sống của chúng kéo dài hơn so với các biến cục bộ thông thường.
- Nếu biến cục bộ tĩnh được khởi tạo với giá trị khác 0, nó sẽ được lưu trữ trong phân vùng dữ liệu đã khởi tạo (Data).
- Nếu biến cục bộ tĩnh được khởi tạo với giá trị 0 hoặc không được khởi tạo, nó sẽ được lưu trữ trong phân vùng BSS (Block Started by Symbol).

- **Chú ý** có thể khai báo 1 biến static cho nhiều chương trình khác nhau. Và ko gây ra xung đột khi thực hiện chương trình
```c
void count()
{
    static int a = 5;
    printf("a = %d", a++);
}

void count1()
{
    static int a = 0;
}
```
### 2.2 Static global variables

#### 2.2.1. Đặc điểm của biến `static` toàn cục
- **Phạm vi**: Biến `static` toàn cục chỉ có thể truy cập được trong tệp nguồn nơi nó được khai báo. Điều này có nghĩa là nó không thể được truy cập từ các tệp nguồn khác, ngay cả khi sử dụng từ khóa `extern`.
- **Thời gian sống**: Biến `static` toàn cục tồn tại trong suốt thời gian chạy của chương trình, từ khi chương trình bắt đầu cho đến khi kết thúc.
- **Khởi tạo**: Biến `static` toàn cục được khởi tạo một lần duy nhất khi chương trình bắt đầu. Nếu không được khởi tạo cụ thể, nó sẽ tự động được khởi tạo với giá trị 0.

#### 2.2.2. Ví dụ

**file1.c**:
```c
#include <stdio.h>

static int count = 0; // Biến static toàn cục

void increment() {
    count++;
    printf("Count: %d\n", count);
}
```

**main.c**:
```c
#include <stdio.h>

// extern int count; // Không thể truy cập biến static toàn cục từ tệp khác

void increment();

int main() {
    increment(); // Output: Count: 1
    increment(); // Output: Count: 2
    return 0;
}
```

Trong ví dụ trên, biến `count` được khai báo là `static` toàn cục trong `file1.c`. Nó chỉ có thể truy cập được trong `file1.c` và không thể truy cập từ `main.c`. Hàm `increment` được sử dụng để tăng giá trị của `count` và in ra giá trị hiện tại.

#### 2.2.3. Lợi ích của biến `static` toàn cục
- **Bảo mật**: Giúp bảo vệ biến khỏi việc truy cập và thay đổi từ các tệp nguồn khác, tăng cường tính bảo mật và tính toàn vẹn của dữ liệu.
- **Quản lý bộ nhớ**: Biến `static` toàn cục được khởi tạo một lần và tồn tại trong suốt thời gian chạy của chương trình, giúp quản lý bộ nhớ hiệu quả hơn.

## 3. Volatile

### 3.1. Đặc điểm của biến `volatile`
- **Không tối ưu hóa**: Trình biên dịch sẽ không tối ưu hóa các truy cập đến biến `volatile`, đảm bảo rằng mỗi lần truy cập đều thực sự đọc hoặc ghi vào bộ nhớ.
- **Thay đổi bất ngờ**: Biến `volatile` có thể thay đổi bởi các yếu tố bên ngoài như phần cứng, các luồng khác, hoặc các tín hiệu.

### 3.2 Sử dụng `volatile`
- **Biến phần cứng**: Khi làm việc với các thanh ghi phần cứng hoặc các cổng I/O.
  ```c
  volatile int *port = (int *)0x1234; // Địa chỉ của một cổng I/O
  ```
- **Biến chia sẻ giữa các luồng**: Khi một biến được truy cập bởi nhiều luồng trong lập trình đa luồng.
  ```c
  volatile int flag = 0;
  ```

### 3.3 Ví dụ
Dưới đây là một ví dụ về cách sử dụng từ khóa `volatile`:

```c
#include <stdio.h>
#include <stdbool.h>

volatile bool flag = false;

void interruptHandler() {
    flag = true; // Biến flag có thể được thay đổi bởi một ngắt
}

int main() {
    while (!flag) {
        // Chờ cho đến khi flag được thay đổi bởi ngắt
    }
    printf("Flag has been set!\n");
    return 0;
}
```

Trong ví dụ trên, biến `flag` được khai báo là `volatile` vì nó có thể được thay đổi bởi một hàm ngắt (interrupt handler). Trình biên dịch sẽ không tối ưu hóa vòng lặp `while (!flag)`, đảm bảo rằng giá trị của `flag` được kiểm tra mỗi lần lặp.

### 3.4. Mục đích `volatile`
- **Đảm bảo tính chính xác**: Đảm bảo rằng giá trị của biến luôn được đọc từ bộ nhớ, không phải từ bộ nhớ đệm của CPU.
- **Tương thích với phần cứng**: Hữu ích khi làm việc với các thiết bị phần cứng mà giá trị của biến có thể thay đổi bất ngờ.

## 4. Register

### 4.1. Đặc điểm của biến `register`
- **Tốc độ truy cập nhanh**: Biến `register` có thể được truy cập nhanh hơn so với các biến lưu trữ trong bộ nhớ chính, vì các thanh ghi của CPU có tốc độ truy cập nhanh hơn.
- **Không có địa chỉ**: Không thể lấy địa chỉ của một biến `register` bằng cách sử dụng toán tử `&`, vì biến này không có địa chỉ bộ nhớ cụ thể.

### 4.2. Ví dụ
Dưới đây là một ví dụ về cách sử dụng từ khóa `register`:

```c
#include <stdio.h>
#include <time.h>

int main() {
    // Lưu thời điểm bắt đầu
    clock_t start_time = clock();
    register int i;

    // Đoạn mã của chương trình
    for (i = 0; i < 200000000; ++i) {
        // Thực hiện một số công việc bất kỳ
    }

    // Lưu thời điểm kết thúc
    clock_t end_time = clock();

    // Tính thời gian chạy bằng miligiây
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Thoi gian chay cua chuong trinh: %f giay\n", time_taken);

    return 0;
}
```

Trong ví dụ trên, biến `i` được khai báo là `register`, yêu cầu trình biên dịch lưu trữ biến này trong một thanh ghi của CPU để tăng tốc độ truy cập.

### 4.3 Sử dụng `register`
- **Vòng lặp**: Khi có một biến được sử dụng nhiều lần trong một vòng lặp, việc khai báo biến đó là `register` có thể giúp tăng hiệu suất.
- **Biến tạm thời**: Các biến tạm thời được sử dụng trong các phép tính toán học hoặc logic phức tạp có thể được khai báo là `register` để tăng tốc độ xử lý.
</details>
