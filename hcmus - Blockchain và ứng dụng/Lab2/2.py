"""
Đây là đoạn code Python sử dụng thư viện turtle để vẽ biểu tượng Yin Yang. Chúng ta hãy phân tích từng phần:

Đầu tiên import thư viện turtle:

```python
from turtle import *
```

Tiếp theo định nghĩa hàm `yin()` để vẽ nửa biểu tượng Yin hoặc Yang:

```python
def yin(radius, color1, color2):
```

Các tham số truyền vào:

- `radius`: bán kính vòng tròn lớn
- `color1`: màu nền
- `color2`: màu vòng tròn nhỏ bên trong

Bên trong hàm `yin()`:

- Dùng các hàm `width()`, `color()`, `begin_fill()`, `circle()`,... để vẽ nửa hình tròn với màu nền `color1`
- Vẽ vòng tròn nhỏ màu `color2` bên trong
- Dùng các hàm `up()`, `forward()`, `backward()` để di chuyển con trỏ turtle

Tiếp theo định nghĩa hàm `main()` để vẽ toàn bộ biểu tượng Yin Yang:

- Gọi `yin()` 2 lần với các màu nền đối lập đen/trắng
- Dùng `ht()` ẩn con trỏ turtle
- Trả về chuỗi `Done!`

Cuối cùng gọi `main()` nếu file được chạy trực tiếp.

Như vậy code vẽ biểu tượng Yin Yang bằng Python turtle.
"""
from turtle import *


def yin(radius, color1, color2):
    width(3)
    color("black", color1)
    begin_fill()
    circle(radius/2., 180)
    circle(radius, 180)
    left(180)
    circle(-radius/2., 180)
    end_fill()
    left(90)
    up()
    forward(radius*0.35)
    right(90)
    down()
    color(color1, color2)
    begin_fill()
    circle(radius*0.15)
    end_fill()
    left(90)
    up()
    backward(radius*0.35)
    down()
    left(90)


def main():
    reset()
    yin(200, "black", "white")
    yin(200, "white", "black")
    ht()
    return "Done!"


if __name__ == '__main__':
    main()
    mainloop()