USE QLDeTai

/*1. Xuất mã và họ tên giáo viên có tham gia đề tài do trưởng bộ môn của họ là chủ nhiệm.*/
SELECT DISTINCT G.MAGV, G.HOTEN
FROM GIAOVIEN G
JOIN DETAI D ON G.MAGV = D.GVCNDT
JOIN BOMON BM ON G.MABM = BM.MABM
WHERE D.GVCNDT = BM.TRUONGBM;


/*2. Xuất mã, họ tên, và tuổi của các giáo viên đã từng tham gia công việc thiết kế hoặc đã
	từng chủ nhiệm đề tài có công việc liên quan đến xác định yêu cầu.*/
SELECT DISTINCT G.MAGV, G.HOTEN, YEAR(GETDATE()) - YEAR(G.NGSINH) AS Tuoi
FROM GIAOVIEN G
JOIN THAMGIADT TG ON G.MAGV = TG.MAGV
JOIN CONGVIEC CV ON TG.MADT = CV.MADT
JOIN DETAI D ON TG.MADT = D.MADT
WHERE CV.TENCV = N'Xác định yêu cầu' OR D.TENDT = N'Xác định yêu cầu';


/*3. Xuất mã và họ tên các trưởng khoa có tham gia đề tài thuộc chủ đề “nghiên cứu” nhưng
	chưa từng tham gia đề tài nào thuộc chủ đề “ứng dụng”.*/
SELECT DISTINCT G.MAGV, G.HOTEN
FROM GIAOVIEN G
JOIN DETAI D ON G.MAGV = D.GVCNDT
JOIN CHUDE C1 ON D.MACD = C1.MACD AND C1.TENCD = N'Nghiên cứu phát triển'
JOIN KHOA K ON G.MAGV = K.TRUONGKHOA
WHERE G.MAGV NOT IN (
    SELECT DISTINCT G2.MAGV
    FROM GIAOVIEN G2
    JOIN DETAI D2 ON G2.MAGV = D2.GVCNDT
    JOIN CHUDE C2 ON D2.MACD = C2.MACD AND C2.TENCD = N'Ứng dụng công nghệ'
);


/*4. Xuất mã, tên chủ đề, cấp quản lý (capql) và số lượng đề tài có kinh phí từ 100 triệu trở
	lên theo từng cấp quản lý của mỗi chủ đề.*/
SELECT C.MACD, C.TENCD, D.CAPQL, COUNT(*) AS SoLuongDeTai
FROM CHUDE C
JOIN DETAI D ON C.MACD = D.MACD
WHERE D.KINHPHI >= 100000000
GROUP BY C.MACD, C.TENCD, D.CAPQL;


/*5. Xuất mã, họ tên giáo viên, họ tên quản lý chuyên môn của giáo viên (nếu không có
	quản lý để ký hiệu “-”) của các giáo viên có tham gia đề tài được chủ nhiệm bởi giáo
	viên khác bộ môn.*/
SELECT G.MAGV, G.HOTEN, 
    COALESCE((SELECT HOTEN FROM GIAOVIEN WHERE MAGV = G.GVQLCM), '-') AS HoTenQuanLy
FROM GIAOVIEN G
WHERE G.MAGV IN (
    SELECT DISTINCT TG.MAGV
    FROM THAMGIADT TG
    JOIN GIAOVIEN GV ON TG.MADT IN (
        SELECT MADT 
        FROM DETAI 
        WHERE GVCNDT <> TG.MAGV
    )
);


/*6. Xuất mã, họ tên giáo viên và tổng số lượng giáo viên mà họ quản lý chuyên môn (nếu
	không quản lý ai, giá trị xuất ra là 0).*/
SELECT G.MAGV, G.HOTEN, 
       COALESCE((SELECT COUNT(*) 
                 FROM GIAOVIEN 
                 WHERE GVQLCM = G.MAGV), 0) AS SoLuongQuanLy
FROM GIAOVIEN G;


/*7. Xuất mã, họ tên giáo viên, tên khoa mà giáo viên thuộc về của các giáo viên từng chủ
	nhiệm trên 2 đề tài có kinh phí >= 100 triệu.*/

/*8. Xuất mã, tên đề tài, tên và STT công việc có đông giáo viên tham gia nhất.*/
SELECT D.MADT, D.TENDT, CV.TENCV, CV.SOTT
FROM DETAI D, CONGVIEC CV
WHERE D.MADT = CV.MADT
AND (CV.MADT, CV.SOTT) IN (
    SELECT TOP 1 MADT, SOTT
    FROM THAMGIADT
    GROUP BY MADT, SOTT
    ORDER BY COUNT(*) DESC
);


/*9. Xuất mã và họ tên giáo viên có lương lớn nhất ở từng khoa theo các yêu cầu sau:
	• Cách 1: Có dùng lượng từ ALL hoặc hàm kết hợp MAX.
	• Cách 2: Không dùng bất cứ lượng từ hay hàm kết hợp nào.*/
-- Cách 2: Không sử dụng bất kỳ lượng từ hoặc hàm kết hợp nào
SELECT G1.MAGV, G1.HOTEN
FROM GIAOVIEN G1
WHERE NOT EXISTS (
    SELECT 1
    FROM GIAOVIEN G2
    WHERE G2.MABM = G1.MABM AND G2.LUONG > G1.LUONG
);


/*10.Xuất mã và tên khoa có đông giáo viên từng chủ nhiệm đề tài nhất.*/
SELECT K.MAKHOA, K.TENKHOA
FROM KHOA K
WHERE K.MAKHOA IN (
    SELECT TOP 1 WITH TIES G.MABM
    FROM GIAOVIEN G
    JOIN DETAI D ON G.MAGV = D.GVCNDT
    GROUP BY G.MABM
    ORDER BY COUNT(*) DESC
);


/*11.Xuất mã và tên bộ môn có nhiều giáo viên có quản lý chuyên môn nhất.*/
SELECT TOP 1 WITH TIES B.MABM, B.TENBM
FROM BOMON B
JOIN GIAOVIEN G ON B.MABM = G.MABM
WHERE G.GVQLCM IS NOT NULL
GROUP BY B.MABM, B.TENBM
ORDER BY COUNT(DISTINCT G.MAGV) DESC;


/*12.Xuất mã, họ tên giáo viên và tổng tiền phụ cấp mà giáo viên nhận được theo từng năm.
	Biết rằng tiền phụ cấp được tính từ hệ số phụ cấp cho các công việc mà giáo viên tham
	gia trong năm đó (có ngày kết thúc trong năm đang xét) với các quy định như sau:
		• Kết quả “Đạt”, Phụ cấp = Hệ số * Lương tháng.
		• Còn lại, Phụ cấp = Hệ số * (1/2 Lương tháng).*/

/*13.Xuất mã và họ tên giáo viên thuộc khoa “Công nghệ thông tin” có tham gia tất cả đề tài
	thuộc cấp ĐHQG.*/
SELECT MAGV, HOTEN
FROM GIAOVIEN
WHERE MABM = 'CNTT'
AND NOT EXISTS (
    SELECT DISTINCT D.MADT
    FROM DETAI D
    WHERE D.GVCNDT = GIAOVIEN.MAGV
    AND D.CAPQL <> 'ĐHQG'
);


/*14.Xuất mã, họ tên giáo viên thuộc bộ môn “Mạng máy tính” tham gia tất cả công việc
	liên quan đến đề tài thuộc chủ đề “ứng dụng”.*/
SELECT G.MAGV, G.HOTEN
FROM GIAOVIEN G
JOIN BOMON BM ON G.MABM = BM.MABM
WHERE BM.TENBM = N'Mạng máy tính'
AND NOT EXISTS (
    SELECT 1
    FROM DETAI D
    JOIN CHUDE C ON D.MACD = C.MACD
    JOIN CONGVIEC CV ON D.MADT = CV.MADT
    WHERE G.MAGV = D.GVCNDT
    AND C.TENCD = N'Ứng dụng công nghệ'
);


/*15.Xuất mã, họ tên trưởng khoa có các đề tài từng chủ nhiệm bao phủ tất cả các chủ đề.*/
SELECT G.MAGV, G.HOTEN
FROM GIAOVIEN G
JOIN KHOA K ON G.MAGV = K.TRUONGKHOA
WHERE EXISTS (
    SELECT DISTINCT MACD
    FROM CHUDE
    EXCEPT
    SELECT DISTINCT D.MACD
    FROM DETAI D
    WHERE D.GVCNDT = G.MAGV
)
GROUP BY G.MAGV, G.HOTEN;


/*16.Xuất mã, họ tên trưởng bộ môn có các đề tài từng tham gia liên quan đến tất cả các cấp.*/

/*17.Xuất mã, tên chủ đề có đề tài có tất cả giáo viên có mã tận cùng là số chẵn tham gia.*/
SELECT C.MACD, C.TENCD
FROM CHUDE C
JOIN DETAI D ON C.MACD = D.MACD
GROUP BY C.MACD, C.TENCD
HAVING COUNT(*) = (
    SELECT COUNT(*)
    FROM GIAOVIEN
    WHERE RIGHT(MAGV, 1) % 2 = 0
);


/*18.Xuất mã, tên đề tài, tên công việc có tất cả giáo viên có lương 2000-3000 tham gia.*/
SELECT D.MADT, D.TENDT, CV.TENCV
FROM DETAI D
JOIN CONGVIEC CV ON D.MADT = CV.MADT
WHERE D.MADT NOT IN (
    SELECT TG.MADT
    FROM THAMGIADT TG
    JOIN GIAOVIEN G ON TG.MAGV = G.MAGV
    WHERE G.LUONG < 2000 OR G.LUONG > 3000
);
