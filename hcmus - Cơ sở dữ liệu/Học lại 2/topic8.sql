/***** Bài tập trên lớp *****/
/* Câu a */
CREATE PROCEDURE sp_HelloWorld
AS
	Print 'Hello World!!!'
	
-- Test Câu a
Exec sp_HelloWorld


/* Câu b */
CREATE PROCEDURE sp_Tong_2_Print @So1 int, @So2 int
AS
	DECLARE @Tong int
	SET @Tong = @So1 + @So2
	Print @Tong

-- Test Câu b
Exec sp_Tong_2_Print 1, -2


/* Câu c */
CREATE PROCEDURE sp_Tong_2 @So1 int, @So2 int, @Tong int out
AS
	SET @Tong = @So1 + @So2

-- Test Câu c
DECLARE @Sum int
Exec sp_Tong_2 1, -2, @Sum out
Print @Sum


/* Câu d */
CREATE PROCEDURE sp_Tong_3_In @So1 int, @So2 int,@So3 int
AS
	DECLARE @Tong int
	Exec sp_Tong_2 @So1, @So2, @Tong out
	SET @Tong = @Tong + @So3
	Print @Tong

-- Test Câu d
Exec sp_Tong_3_In 1, -2, 4


/* Câu e */
CREATE PROCEDURE sp_Tong_MN @m int, @n int
AS
	DECLARE @Tong int
	DECLARE @i int
	SET @Tong = 0
	SET @i = @m
	
	WHILE (@i < @n)
	BEGIN
		SET @Tong = @Tong + @i
		SET @i = @i + 1
	END
	
	Print @Tong

-- Test Câu e
Exec sp_Tong_MN 1,6


/* Câu f */
CREATE PROCEDURE sp_check_NgTo @num int, @check bit out
AS
	DECLARE @bound float
	DECLARE @i int
	SET @check = 1
	SET @i = 2
	SET @bound = SQRT(@num)
	
	While (@i <= @bound)
	BEGIN
		IF (@num % @i = 0)
			BEGIN
				SET @check = 0
				break
			END
		SET @i = @i + 1		
	END

-- Test Câu f
DECLARE @check bit
Exec sp_check_NgTo 5, @check out
IF (@check = 1)
	BEGIN
		Print N'5 là số nguyên tố.'
	END
ELSE
	BEGIN
		Print N'5 không là số nguyên tố.'
	END
	
Exec sp_check_NgTo 1, @check out
IF (@check = 1)
	BEGIN
		Print N'1 là số nguyên tố.'
	END
ELSE
	BEGIN
		Print N'1 không là số nguyên tố.'
	END
	
Exec sp_check_NgTo 4, @check out
IF (@check = 1)
	BEGIN
		Print N'4 là số nguyên tố.'
	END
ELSE
	BEGIN
		Print N'4 không là số nguyên tố.'
	END


/* Câu g */		
CREATE PROCEDURE sp_tong_NgTo_MN @m int, @n int
AS
	DECLARE @Tong int
	DECLARE @i int
	DECLARE @check bit
	SET @Tong = 0
	SET @i = @m
	
	While (@i <= @n)
	BEGIN
		Exec sp_check_NgTo @i, @check out
		IF (@check = 1)
			BEGIN
				SET @Tong = @Tong + @i
			END
			
		SET @i = @i + 1
	END
	
	Print N'Tổng các số nguyên tố trong [' + cast(@m as varchar(12)) + N', ' + cast(@n as varchar(12)) + '] = ' + cast(@Tong as varchar(12))

-- Test Câu g
Exec sp_tong_NgTo_MN 1, 5


/* Câu h */
CREATE PROCEDURE sp_UCLN @a int, @b int, @ret int out
AS
	SET @a = ABS(@a)
	SET @b = ABS(@b)
	
	IF (@a = 0 OR @b = 0)
		BEGIN
			SET @ret = @a + @b
		END
	ELSE
		BEGIN
			While (@a <> @b)
			BEGIN
				IF (@a > @b)
					SET @a = @a - @b
				ELSE
					SET @b = @b - @a
			END
		END
	
	SET @ret = @a

-- Test Câu h
DECLARE @UCLN int
Exec sp_UCLN -4, 14, @UCLN out
Print @UCLN


/* Câu i */
CREATE PROCEDURE sp_BCNN @a int, @b int, @ret int out
AS
	DECLARE @temp int 
	
	Exec sp_UCLN @a, @b, @temp out
	
	SET @ret = ABS(@a*@b)/@temp

-- Test Câu i
DECLARE @BCNN int
Exec sp_BCNN 4, 14, @BCNN out
Print @BCNN


/* Câu j */
CREATE PROCEDURE sp_DSGV
AS
	SELECT * FROM GIAOVIEN

-- Test Câu j
Exec sp_DSGV


/* Câu k */
CREATE PROCEDURE sp_SLDT @MaGV varchar(9)
AS
	DECLARE @ret int
	SET @ret = (SELECT COUNT(DISTINCT MADT) FROM THAMGIADT WHERE MAGV = @MaGV GROUP BY MAGV)
	Print N'Số lượng đề tài của GV có MAGV = ' + @MaGV + ' là ' + CAST(@ret AS VARCHAR(12))

-- Test Câu k
Exec sp_SLDT '001'


/* Câu l */
CREATE PROCEDURE sp_TTGV @MaGV varchar(9)
AS
	DECLARE @HoTen nvarchar(30)
	SET @HoTen = (SELECT HOTEN FROM GIAOVIEN WHERE MAGV = @MaGV)
	Print N'Họ tên: ' + @HoTen
	
	DECLARE @Luong decimal(18,1)
	SET @Luong = (SELECT LUONG FROM GIAOVIEN WHERE MAGV = @MaGV)
	Print N'Lương: ' + CAST(@Luong AS VARCHAR(12))
	
	DECLARE @NGSINH date
	SET @NGSINH = (SELECT NGSINH FROM GIAOVIEN WHERE MAGV = @MaGV)
	Print N'Ngày sinh: ' + CAST(@NGSINH AS VARCHAR(12))
	
	DECLARE @DiaChi nvarchar(50)
	Set @DiaChi = (SELECT DIACHI FROM GIAOVIEN WHERE MAGV = @MaGV)
	Print N'Địa chỉ: ' + @DiaChi
	
	DECLARE @SLDT int
	SET @SLDT = (SELECT COUNT(DISTINCT MADT) FROM THAMGIADT WHERE MAGV = @MaGV GROUP BY MAGV)
	Print N'SLDT: ' + CAST(@SLDT AS VARCHAR(12))
	
	DECLARE @SLNT int
	SET @SLNT = (SELECT COUNT(*) FROM NGUOITHAN WHERE MAGV = @MaGV GROUP BY MAGV)
	Print N'SLNT: ' + CAST(@SLNT AS VARCHAR(12))

-- Test Câu l
Exec sp_TTGV '001'


/* Câu m */
CREATE PROCEDURE sp_CheckGVExist @MaGV varchar(9), @check bit out
AS
	IF (EXISTS(SELECT * FROM GIAOVIEN WHERE MAGV = @MaGV))
		BEGIN
			Print N'MAGV = ' + @MaGV + N' -> tồn tại giáo viên.'
			SET @check = 1
		END
	ELSE
		BEGIN
			Print N'MAGV = ' + @MaGV + N' -> không tồn tại giáo viên!'
			SET @check = 0
		END
		
-- Test Câu m
DECLARE @check bit
Exec sp_CheckGVExist '001', @check out
Exec sp_CheckGVExist '101', @check out


/* Câu n */
CREATE PROCEDURE sp_CheckRuleGV @MaGV varchar(9), @MaDT varchar(3), @check bit out
AS
	DECLARE @GVCNDT varchar(3)
	SET @GVCNDT = (SELECT GVCNDT FROM DETAI WHERE MADT = @MaDT)
	
	IF ((SELECT MABM FROM GIAOVIEN WHERE MAGV = @MaGV) = (SELECT MABM FROM GIAOVIEN WHERE MAGV = @GVCNDT))
		BEGIN
			Print 'True'
			Set @check = 1
		END
	ELSE
		BEGIN
			Print 'False'
			Set @check = 0
		END

-- Test Câu n
DECLARE @check bit
Exec sp_CheckRuleGV '001', '003', @check out
Exec sp_CheckRuleGV '001', '007', @check out


/* Câu o */
CREATE PROCEDURE sp_PhanCongCongViec @MaGV varchar(3), @MaDT varchar(3), @Stt int, @PhuCap int, @Ketqua nvarchar(3)
AS
	DECLARE @check bit
	SET @check = 1
	
	IF (NOT EXISTS(SELECT * FROM GIAOVIEN WHERE MAGV = @MaGV))
		BEGIN
			Print N'Lỗi! Mã GV không tồn tại!'
			SET @check = 0
		END
	
	IF (NOT EXISTS(SELECT * FROM CONGVIEC WHERE MADT = @MaDT AND SOTT = @Stt))
		BEGIN
			Print N'Lỗi! Công việc không tồn tại!'
			SET @check = 0
		END
	
	-- Câu n
	DECLARE @GVCNDT varchar(3)
	SET @GVCNDT = (SELECT GVCNDT FROM DETAI WHERE MADT = @MaDT)
	
	IF (@check = 1 AND (SELECT MABM FROM GIAOVIEN WHERE MAGV = @MaGV) <> (SELECT MABM FROM GIAOVIEN WHERE MAGV = @GVCNDT))
		BEGIN
			Print N'Lỗi! Đề tài không do bộ môn của GV làm chủ nhiệm!'
			Set @check = 0
		END
	
	-- Thêm phân công
	IF (@check = 1)
		BEGIN
			INSERT INTO THAMGIADT(MAGV, MADT, STT, PHUCAP, KETQUA)
			VALUES (@MaGV, @MaDT, @Stt, @PhuCap, @Ketqua)
			Print N'Phân công thành công.'
		END

-- Test Câu o
Exec sp_PhanCongCongViec '001', '002', 3, 0, NULL


/* Câu p */
CREATE PROCEDURE sp_XoaGV @MaGV varchar(9)
AS
	DECLARE @check bit
	SET @check = 1
	
	IF (EXISTS(SELECT * FROM GIAOVIEN WHERE MAGV = @MaGV))
		BEGIN
			IF (EXISTS(SELECT * FROM NGUOITHAN WHERE MAGV = @MaGV))
				BEGIN
					Print N'Giáo viên tồn tại người thân! Lỗi!'
					SET @check = 0
				END
				
			IF (EXISTS(SELECT * FROM THAMGIADT WHERE MAGV = @MaGV))
				BEGIN
					Print N'Giáo viên có tham gia đề tại! Lỗi!'
					SET @check = 0
				END
				
			IF (EXISTS(SELECT * FROM BOMON WHERE TRUONGBM = @MaGV))
				BEGIN
					Print N'Giáo viên đang là trưởng bộ môn! Lỗi!'
					SET @check = 0
				END
				
			IF (EXISTS(SELECT * FROM KHOA WHERE TRUONGKHOA = @MaGV))
				BEGIN
					Print N'Giáo viên đang là trưởng khoa! Lỗi!'
					SET @check = 0
				END
				
			IF (EXISTS(SELECT * FROM DETAI WHERE GVCNDT = @MaGV))
				BEGIN
					Print N'Giáo viên đang chủ nhiệm đề tài! Lỗi!'
					SET @check = 0
				END
				
			IF (EXISTS(SELECT * FROM GV_DT WHERE MAGV = @MaGV))
				BEGIN
					Print N'Giáo viên có tồn tại số điện thoại! Lỗi!'
					SET @check = 0
				END
				
			IF (@check = 1)
				BEGIN
					DELETE FROM GIAOVIEN WHERE MAGV = @MaGV
					Print N'Xóa thành công.'
				END
		END
	ELSE
		Print N'Không tồn tại giáo viên có MAGV = ' + @MaGV

-- Test Câu p
Exec sp_XoaGV '100'


/* Câu q */
-- using cursor
CREATE PROCEDURE sp_DSGVAll
AS
	DECLARE cs_DSGV CURSOR FOR (SELECT MAGV FROM GIAOVIEN)
	OPEN cs_DSGV
	
	DECLARE @MaGV varchar(3)
	FETCH NEXT FROM cs_DSGV INTO @MaGV
	
	WHILE (@@FETCH_STATUS = 0)
	BEGIN
		DECLARE @HoTen nvarchar(30)
		SET @HoTen = (SELECT HOTEN FROM GIAOVIEN WHERE MAGV = @MaGV)
		Print N'Họ tên: ' + @HoTen
		
		DECLARE @Luong decimal(18,1)
		SET @Luong = (SELECT LUONG FROM GIAOVIEN WHERE MAGV = @MaGV)
		Print N'Lương: ' + CAST(@Luong AS VARCHAR(12))
		
		DECLARE @NGSINH date
		SET @NGSINH = (SELECT NGSINH FROM GIAOVIEN WHERE MAGV = @MaGV)
		Print N'Ngày sinh: ' + CAST(@NGSINH AS VARCHAR(12))
		
		DECLARE @DiaChi nvarchar(50)
		Set @DiaChi = (SELECT DIACHI FROM GIAOVIEN WHERE MAGV = @MaGV)
		Print N'Địa chỉ: ' + @DiaChi
		
		DECLARE @SLDT int
		SET @SLDT = (SELECT COUNT(DISTINCT MADT) FROM THAMGIADT WHERE MAGV = @MaGV GROUP BY MAGV)
		Print N'SLDT: ' + CAST(@SLDT AS VARCHAR(12))
		
		DECLARE @SLNT int
		SET @SLNT = (SELECT COUNT(*) FROM NGUOITHAN WHERE MAGV = @MaGV GROUP BY MAGV)
		Print N'SLNT: ' + CAST(@SLNT AS VARCHAR(12))
		
		DECLARE @SoGVQL int
		SET @SoGVQL = (SELECT COUNT(*) FROM GIAOVIEN WHERE GVQLCM = @MaGV)
		Print N'Số GV mà GV quản lý: ' + CAST(@SoGVQL AS VARCHAR(12))
		
		Print '-------------------------------------------------------------'
		FETCH NEXT FROM cs_DSGV INTO @MaGV  
	END
	
	CLOSE cs_DSGV
	DEALLOCATE cs_DSGV

-- Test Câu q
Exec sp_DSGVAll


/* Câu r */
CREATE PROCEDURE sp_CheckRuleGV_AB @MaGVA varchar(9), @MaGVB varchar(9)
AS
	IF ((SELECT MABM FROM GIAOVIEN WHERE MAGV = @MaGVA) = (SELECT MABM FROM GIAOVIEN WHERE MAGV = @MaGVB))
		IF (EXISTS(SELECT * FROM BOMON WHERE TRUONGBM = @MaGVA))
			IF ((SELECT LUONG FROM GIAOVIEN WHERE MAGV = @MaGVA) < (SELECT LUONG FROM GIAOVIEN WHERE MAGV = @MaGVB))
				BEGIN
					Print 'FALSE'
				END
			ELSE
				BEGIN
					Print 'TRUE'
				END
		ELSE 
			IF (EXISTS(SELECT * FROM BOMON WHERE TRUONGBM = @MaGVB))
				IF ((SELECT LUONG FROM GIAOVIEN WHERE MAGV = @MaGVA) > (SELECT LUONG FROM GIAOVIEN WHERE MAGV = @MaGVB))
					Print 'FALSE'
				ELSE
					Print 'TRUE'
			ELSE
				Print 'TRUE'
	ELSE
		Print 'TRUE'

-- Test Câu r
Exec sp_CheckRuleGV_AB '003', '002'


/* Câu s */
CREATE PROCEDURE sp_AddGV @MaGV varchar(9), @HoTen nvarchar(30), @Luong int, @Phai nchar(3), @NgSinh date, @DiaChi nvarchar(50), @GVQLCM varchar(3), @MaBM  nchar(4)
AS
	DECLARE @check bit
	SET @check = 1
	
	IF (EXISTS(SELECT * FROM GIAOVIEN WHERE HOTEN = @HoTen))
		BEGIN
			Print N'Lỗi! Trùng họ tên GV khác'
			SET @check = 0
		END
		
	IF (YEAR(GetDate()) - YEAR(@NgSinh) < 18)
		BEGIN
			Print N'Lỗi! Tuổi < 18'
			SET @check = 0
		END
		
	IF (@Luong <= 0)
		BEGIN
			Print N'Lỗi! Lương < 0'
			SET @check = 0
		END
	
	IF (@check = 1)
		BEGIN
			INSERT INTO GIAOVIEN(MAGV, HOTEN, LUONG, PHAI, NGSINH, DIACHI, GVQLCM, MABM)
			VALUES (@MaGV, @HoTen, @Luong, @Phai, @NgSinh, @DiaChi, @GVQLCM, @MaBM)
			Print N'Thêm thành công!'
		END

-- Test Câu s
Exec sp_AddGV '100', N'Trần Quốc Bảo', 1000, N'Nam', '01/01/1997', N'ABC HCM', NULL, NULL


/* Câu t */
CREATE PROCEDURE sp_AutoMaGV @MaGV varchar(3) out
AS
	DECLARE @num int
	DECLARE @temp varchar(3)
	SET @num = 1
	
	WHILE (1=1)
	BEGIN
		IF (@num < 10)
			BEGIN
				SET @temp = '00' + CAST(@num as varchar(1))
			END
		ELSE IF (@num < 100)
			BEGIN
				SET @temp = '0' + CAST(@num as varchar(2))
			END
		ELSE
			BEGIN
				SET @temp = CAST(@num as varchar(3))
			END
		
		IF (NOT EXISTS(SELECT * FROM GIAOVIEN WHERE MAGV = @temp))
			BEGIN
				Set @MaGV = @temp
				break
			END
		
		SET @num = @num + 1
	END

-- Test câu t
DECLARE @MaGV varchar(3)
Exec sp_AutoMaGV @MaGV out
Print @MaGV



/***** Bài tập về nhà *****/ 
/* Câu 1 */
CREATE PROCEDURE spDatPhong @makh varchar(9), @maphong varchar(9), @ngaydat date
AS
	DECLARE @check bit
	SET @check = 1
	
	-- Kiểm tra mã khách hàng có tồn tại hay không?
	IF (NOT EXISTS(SELECT * FROM KHACH WHERE MaKH = @makh))
		BEGIN
			Print N'Lỗi! Mã khách hàng không tồn tại!'
			SET @check = 0
		END
	
	-- Kiểm tra mã phòng có tồn tại hay không?
	IF (NOT EXISTS(SELECT * FROM PHONG WHERE MaPhong = @maphong))
		BEGIN
			Print N'Lỗi! Mã phòng không tồn tại!'
			SET @check = 0
		END
	
	-- Kiểm tra phòng ứng với mã phòng có đang "Rảnh" hay không?
	IF (NOT ((SELECT Tinh FROM PHONG WHERE MaPhong = @maphong) = N'Rảnh'))
		BEGIN
			Print N'Lỗi! Phòng ứng với mã phòng đã được đặt!'
			SET @check = 0
		END
		
	-- Nếu check hợp lệ thì ghi thông tin đặt phòng xuống CSDL
	DECLARE @madatphong int
	-- Nếu DATPHONG chưa có dữ liệu nào
	IF (NOT EXISTS(SELECT * FROM DATPHONG))
		BEGIN
			-- Mã trong DATPHONG sẽ bắt đầu từ 1
			SET @madatphong = 1
		END
	-- Nếu DATPHONG đã có dữ liệu
	ELSE
		BEGIN
			SET @madatphong = 1 + (SELECT MAX(Ma) FROM DATPHONG GROUP BY Ma)
		END
		
	IF (@check = 1)
		BEGIN
			INSERT INTO DATPHONG(Ma, MaKH, MaPhong, NgayDP, NgayTra, ThanhTien)
			VALUES (@madatphong, @makh, @maphong, @ngaydat, NULL, NULL)
			Print N'Đặt phòng thành công'
			-- Sau khi đặt phòng thành công cập nhật lại trạng thái PHONG
			UPDATE PHONG
			SET Tinh = N'Bận'
			WHERE MaPhong = @maphong
		END

-- Test Câu 1
-- Đã tạo CSDL mẫu để test thử
-- TRUE
Exec spDatPhong '001', '001', '11/25/2017'
-- FALSE
Exec spDatPhong '101', '101', '11/25/2017'


/* Câu 2 */
CREATE PROCEDURE spTraPhong @madp varchar(9), @makh varchar(9)
AS
	DECLARE @check bit
	SET @check = 1
	
	-- Kiểm tra tính hợp lệ của mã đặt phòng và mã khách hàng
	IF (NOT EXISTS(SELECT * FROM DATPHONG WHERE Ma = @madp AND MaKH = @makh))
		BEGIN
			Print N'Lỗi! Khách hàng chưa thực hiện việc đặt phòng.'
			SET @check = 0
		END
	
	IF (@check = 1)
		BEGIN
			-- Ngày trả phòng chính là ngày hiện hành
			UPDATE DATPHONG
			SET NgayTra = GetDate()
			WHERE Ma = @madp AND MaKH = @makh
			
			-- Tiền thanh toán = Số ngày x đơn giá phòng
			DECLARE @songay int
			SET @songay = DATEDIFF(D, SELECT NgayDP FROM DATPHONG WHERE Ma = @madp AND MaKH = @makh, GetDate())
			
			DECLARE @maphong varchar(9)
			SET @maphong = (SELECT MaPhong FROM DATPHONG WHERE Ma = @madp AND MaKH = @makh)
			
			DECLARE @dongia int
			SET @dongia = (SELECT DonGia FROM PHONG WHERE MaPhong = @maphong)
			
			UPDATE DATPHONG
			SET ThanhTien = @songay * @dongia
			WHERE Ma = @madp AND MaKH = @makh
			
			-- Trả phòng xong, cập nhật lại trạng thái PHONG
			UPDATE PHONG
			SET Tinh = N'Rảnh'
			WHERE MaPhong = @maphong
			
			Print N'Trả phòng thành công.'
		END
		
-- Test Câu 2
-- Đã tạo CSDL mẫu để test thử
-- TRUE
Exec spTraPhong '001', '001'
-- FALSE
Exec spTraPhong '101', '121'