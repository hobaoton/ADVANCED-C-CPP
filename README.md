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


