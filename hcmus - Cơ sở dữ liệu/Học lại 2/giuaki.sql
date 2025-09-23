-- MSSV: 20127318
-- Họ tên: Phan Trí Tài
-- Hàng: 1
-- Cột : 4
-- Đê thi: 4
--Phòng thi: C23A


/*** Câu 1: Tạo bảng***/
GO
CREATE DATABASE QLHocSinh
GO
USE QLHocSinh


CREATE TABLE MONHOC (
    MaMon CHAR(5),
    TenMon NVARCHAR(100),
    GVPTChinh NVARCHAR(100),
    LoaiMon NVARCHAR(50),
    SoGVPT INT,
	PRIMARY KEY (MaMon)
);

CREATE TABLE HOCSINH (
    MaHS CHAR(4),
    MaLop CHAR(5),
    NgaySinh DATE,
    HoTen NVARCHAR(100),
    DiaChi NVARCHAR(255),
    DienThoai VARCHAR(15),
    PRIMARY KEY (MaHS, MaLop),
);

CREATE TABLE KETQUA (
    MaHS CHAR(4),
    MaLop CHAR(5),
    MaMon CHAR(5),
    HocKi CHAR(2),
    Diem FLOAT,
    DiemTB FLOAT,
    PRIMARY KEY (MaHS, MaLop, MaMon, HocKi)
);


/*** Câu 2: Tạo khóa ngoại ***/
ALTER TABLE KETQUA
ADD CONSTRAINT FK_KETQUA_HOCSINH
FOREIGN KEY (MaHS, MaLop)
REFERENCES HOCSINH(MaHS, MaLop)

ALTER TABLE KETQUA
ADD CONSTRAINT FK_KETQUA_MONHOC
FOREIGN KEY (MaMon)
REFERENCES MONHOC(MaMon)


/*** Câu 3: Nhập dữ liệu ***/
INSERT MONHOC (MaMon, TenMon, GVPTChinh, LoaiMon, SoGVPT)
VALUES  ('MH001', N'Toán', N'Trần Thị Hương'   , N'Khối A', 10),
		('MH002', N'Lý'  , N'Trần Bình An'     , N'Khối A', 5),
		('MH004', N'Hóa' , N'Nguyễn Minh Huyền', N'Khối A', 4),
		('MH003', N'Sinh', N'Nguyễn Thị Thu'   , N'Khối B', 5)

INSERT HOCSINH (MaHS, MaLop, NgaySinh, HoTen, DiaChi, DienThoai)
VALUES  ('0001', '10A1', '02/12/2008', N'Nguyễn Thị Minh' , N'123 Vườn Lài, Quận Tân Phú'  , '090391123'),
		('0002', '10A1', '11/23/2008', N'Trần Trung Nghĩa', N'45 Phú Thọ Hòa, Quận Tân Phú', '081283771'),
		('0001', '10A2', '11/22/2007', N'Vũ Ánh Nguyệt'   , N'11 Võ Văn Ngân, Quận Thủ Đức', '098878665'),
		('0004', '10A2', '11/11/2008', N'Trần Thu Phương' , N'11 Nguyễn Trãi, Quận 5'      , null),
		('0001', '11A1', '01/10/2008', N'Nguyễn Minh Hùng', null                           , null)

INSERT KETQUA (MaHS, MaLop, MaMon, HocKi, Diem, DiemTB)
VALUES  ('0001', '10A1', 'MH001', 'I' , 9.25, 9.0),
		('0002', '10A1', 'MH001', 'I' , 7.5 , 5.0),
		('0004', '10A2', 'MH001', 'II', 4.5 , 4.0),
		('0001', '10A2', 'MH003', 'I' , 10.0, 10.0),
		('0002', '10A1', 'MH002', 'I' , 7.5 , 7.5),
		('0001', '11A1', 'MH002', 'II', 9.0 , 9.5)

/*** Câu 4 ***/
SELECT *
FROM HOCSINH , KETQUA
WHERE DiaChi IS NULL
AND KETQUA.DiemTB > KETQUA.Diem;

/*** Câu 5 ***/
SELECT MONHOC.MaMon, MONHOC.TenMon, MONHOC.GVPTChinh, COUNT(KETQUA.MaHS) AS SoHocSinhDat
FROM MONHOC
JOIN KETQUA ON MONHOC.MaMon = KETQUA.MaMon
JOIN HOCSINH ON KETQUA.MaHS = HOCSINH.MaHS AND KETQUA.MaLop = HOCSINH.MaLop
WHERE MONHOC.SoGVPT > 5
AND KETQUA.Diem > 5.0
GROUP BY MONHOC.MaMon, MONHOC.TenMon, MONHOC.GVPTChinh;