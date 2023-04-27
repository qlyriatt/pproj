1.

select a.C_NAME ABONENTNAME, qt.C_NAME QRYTYPE, qq.ID QRYID from ST_ABONENTS a
inner join QRY_TYPE qt on qt.C_AB_REF = a.ID
inner join QRY_QUEUE qq on qt.ID = qq.C_QRY_TYPE
fetch next 10 rows only

2.

select C_NAME ABONENTNAME, count(*) CNT from
(
select a.C_NAME, qq.ID from QRY_QUEUE qq
inner join QRY_TYPE qt on qq.C_QRY_TYPE = qt.ID
inner join ST_ABONENTS a on qt.C_AB_REF = a.ID
where extract(hour from cast(qq.C_IN_TIME as timestamp)) < 18 and extract(hour from cast(qq.C_IN_TIME as timestamp)) > 9
)
group by C_NAME

3.

with
    cts as
    (
    select qq.C_QRY_TYPE, count(qq.C_ST) c, qq.C_ST from QRY_QUEUE qq
    group by qq.C_QRY_TYPE, qq.C_ST
    ),
	ctsFail as (select cts.C_QRY_TYPE, cts.c from cts where cts.C_ST = 0),
	ctsSuccess as (select cts.C_QRY_TYPE, cts.c from cts where cts.C_ST = 1),
	prcs as
	(
	select ctsFail.C_QRY_TYPE, round(ctsFail.c / ctsSuccess.c * 100, 2) PRC from ctsFail
	inner join ctsSuccess on ctsFail.C_QRY_TYPE = ctsSuccess.C_QRY_TYPE
	where (ctsFail.c / ctsSuccess.c * 100) > 5
	)

select qt.C_NAME QRYTYPE, PRC from prcs
inner join QRY_TYPE qt on prcs.C_QRY_TYPE = qt.ID

4.

with
    cts as
    (
    select qq.C_QRY_TYPE, count(qq.C_ST) c, qq.C_ST from QRY_QUEUE qq
	group by qq.C_QRY_TYPE, qq.C_ST
	)

select a.C_NAME ABONENTNAME, cts.C_ST STATUS, sum(cts.c) CNT from cts
inner join QRY_TYPE qt on cts.C_QRY_TYPE = qt.ID
inner join ST_ABONENTS a on qt.C_AB_REF = a.ID
group by a.C_NAME, cts.C_ST
order by ABONENTNAME asc, STATUS asc

5.

with
    cts as
    (
    select qq.C_QRY_TYPE, count(qq.C_ST) c, qq.C_ST from QRY_QUEUE qq
    group by qq.C_QRY_TYPE, qq.C_ST
    )

select a.C_NAME ABONENTNAME, sum(c) CNT from cts
inner join QRY_TYPE qt on cts.C_QRY_TYPE = qt.ID
inner join ST_ABONENTS a on qt.C_AB_REF = a.ID
where C_ST = 0
group by a.C_NAME
having sum(c) < 20

6.

with
    cts as
    (
    select qq.C_QRY_TYPE, count(qq.C_ST) c, qq.C_ST from QRY_QUEUE qq
	group by qq.C_QRY_TYPE, qq.C_ST
    ),
	ctsAll as
    (
    select a.C_NAME ABONENTNAME, sum(cts.c) CNT from cts
	inner join QRY_TYPE qt on cts.C_QRY_TYPE = qt.ID
	inner join ST_ABONENTS a on qt.C_AB_REF = a.ID
	group by a.C_NAME
	order by a.C_NAME
	)

select * from ctsAll
where CNT = (select max(CNT) from ctsAll)

7.

with
    cts as
    (
    select qq.C_QRY_TYPE, count(qq.C_ST) c, qq.C_ST from QRY_QUEUE qq
	group by qq.C_QRY_TYPE, qq.C_ST
    ),
	ctsAll as
    (
    select a.C_NAME ABONENTNAME, sum(cts.c) CNT from cts
	inner join QRY_TYPE qt on cts.C_QRY_TYPE = qt.ID
	inner join ST_ABONENTS a on qt.C_AB_REF = a.ID
	group by a.C_NAME
	order by a.C_NAME
	)

select * from ctsAll
order by CNT desc
fetch next 3 rows only

8.

with ctsTime as
    (
    select a.C_NAME name, extract(hour from cast(qq.C_IN_TIME as timestamp)) hour, count(extract(hour from cast(qq.C_IN_TIME as timestamp))) ct from QRY_QUEUE qq
	inner join QRY_TYPE qt on qq.C_QRY_TYPE = qt.ID
	inner join ST_ABONENTS a on qt.C_AB_REF = a.ID
	group by a.C_NAME, extract(hour from cast(qq.C_IN_TIME as timestamp))
    order by a.C_NAME
    )

select hour h, sum(ctsTime.ct) cnt from ctsTime
group by ctsTime.hour
order by cnt desc
fetch next 1 row only

9.

with ctsTime as
    (
    select a.C_NAME name, extract(hour from cast(qq.C_IN_TIME as timestamp)) hour, count(extract(hour from cast(qq.C_IN_TIME as timestamp))) ct from QRY_QUEUE qq
	inner join QRY_TYPE qt on qq.C_QRY_TYPE = qt.ID
	inner join ST_ABONENTS a on qt.C_AB_REF = a.ID
	group by a.C_NAME, extract(hour from cast(qq.C_IN_TIME as timestamp))
    order by a.C_NAME
    )

select name abonentname, hour hh24, round(ct/360, 2) cnt from ctsTime
order by abonentname asc, cnt desc
