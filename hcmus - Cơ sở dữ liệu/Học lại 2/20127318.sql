--1--
SELECT gv.MÃGV, gv.HỌTÊN, k.TÊNKHOA
FROM GIÁOVIÊN gv
JOIN KHOA k ON gv.MÃKHOA = k.MÃKHOA
WHERE k.MÃKHOA IN (
    SELECT MÃKHOA
    FROM BỘMÔN
    GROUP BY MÃKHOA
    ORDER BY COUNT(*) DESC, AVG(LƯƠNG) DESC
    LIMIT 1
);


--2--
SELECT gv.MÃGV, gv.HỌTÊN
FROM GIÁOVIÊN gv
JOIN THAMGIATÀITRỢ tgtt ON gv.MÃGV = tgtt.MÃGV
LEFT JOIN CHỦNHIỆMCN cn ON gv.MÃGV = cn.MÃGV AND tgtt.MÃTÀITRỢ = cn.MÃTÀITRỢ
WHERE tgtt.MÃTÀITRỢ IN (
    SELECT MÃTÀITRỢ
    FROM TÀITRỢ
    WHERE CẤP = N'Trường'
)
AND cn.MÃTÀITRỢ IS NULL;


--3--
SELECT gv.MÃ_GV, gv.HỌ_TÊN
FROM GIÁO_VIÊN gv
JOIN CHỦ_NHIỆM_CN cn ON gv.MÃ_GV = cn.MÃ_GV
JOIN ĐỀ_TÀI dt ON cn.MÃ_TÀI_TRỢ = dt.MÃ_TÀI_TRỢ
JOIN CÔNG_VIỆC cv ON dt.MÃ_CÔNG_VIỆC = cv.MÃ_CÔNG_VIỆC
WHERE dt.CẤP = N'Nhà nước'
AND cv.TÊN_CÔNG_VIỆC LIKE N'nuôi cấy'
AND gv.MÃ_GV IN (
    SELECT MÃ_GV
    FROM CHỦ_NHIỆM_CN
    GROUP BY MÃ_GV
    HAVING COUNT(*) >= 1
);


--4--
SELECT gv.MÃ_GV, gv.HỌ_TÊN
FROM GIÁO_VIÊN gv
JOIN THAM_GIA_TÀI_TRỢ tgtt ON gv.MÃ_GV = tgtt.MÃ_GV
JOIN TÀI_TRỢ tt ON tgtt.MÃ_TÀI_TRỢ = tt.MÃ_TÀI_TRỢ
WHERE tt.CẤP = N'Nhà nước'
GROUP BY gv.MÃ_GV
HAVING COUNT(*) = SUM(CASE WHEN tt.CẤP = N'Nhà nước' THEN 1 ELSE 0 END);
