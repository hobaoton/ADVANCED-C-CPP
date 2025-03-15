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
</details>


# Bai 3 BITMARK
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

