use 0830test
SELECT * FROM 0830test.humen;

alter table humen#修改表
add column aa int;#添加列

alter table humen
drop column aa

alter table humen
modify column aa varchar(1);#修改列属性

alter table humen
drop column aa;#删除列
use disk
select * from t_user

#查询

select * from humen;
select num from humen;
select num,age from humen;
select * from humen where num>2;
select * from humen where num>2 and num<4;
#模糊查询
select sname from humen where sname like 'w%';
select * from humen where sname like 'q%';
select * from humen where sname like '_l%';
#添加
insert into humen values(1,'ll','女','19');
insert into humen values(2,'wl','男','19');
insert into humen values(3,'cl','女','19');
insert into humen values(4,'ql','男','19');
insert into humen (num,sname) values(3,'kk');

#修改
update humen set sex='女';
update humen set sex='女' where num =2;

#删除
delete from humen;
delete from humen where num=1;

use 0830test;

#查找limit
select * from humen limit 2;#前两行
select * from humen limit 1,2;#偏移一行，显示两行

#排序查找
select * from humen order by age asc,num desc;#查找表，按年龄升序，标号降序

#聚合函数
select count(num) from humen;

#求出表中男女个数
select count(sex) from humen where sex='女'; 
select count(sex) from humen where sex='男'; 

select * from humen where sex='女' order by num asc;
#复合语句 1 from humen 2 where条件 3 group 分组(+having 条件) 4 select显示 5 order排序

select sex,count(sex) from humen where num!=1 group by sex having count(sex)>1 order by count(sex) desc;

#ifnull（a,b）语句如果a为null返回b，否则返回a
select ifnull(0,9);
#多表查询
#内联
select * from student s
inner join sc on sc.Snum=s.Snum;

#左联
select * from student s
left join sc on sc.Snum=s.Snum;

#右联
select * from student s
right join sc on sc.Snum=s.Snum;

#笛卡尔积
select * from student,sc where student.Snum=sc.Snum;

#嵌套
select * from sc;
select *,
(select score from sc where cnum='01'  and sc.Snum=student.Snum) 's','aa' 
from student; 
select *,'aa' s from student; 
select score from sc;




#1、查询"01"课程比"02"课程成绩高的学生的信息及课程分数
#1.1、查询同时存在"01"课程和"02"课程的情况\

select *,(select score from sc where cnum='01' and student.Snum=sc.Snum) sc01,
(select score from sc where cnum='02' and student.Snum=sc.Snum) sc02
 from student;
 #1
 select * from (select *,
 (select score from sc where cnum='01' and student.Snum=sc.Snum) sc01,
(select score from sc where cnum='02' and student.Snum=sc.Snum) sc02
 from student) a 
 where sc01>sc02;

 #1.1
select * from student left join (select sc01.Snum,Sc01.Cnum cnum1,sc01.score score1,sc02.cnum cnum2,sc02.score score2
from (select * from sc where cnum='01') sc01
 inner join (select * from sc where cnum='02') sc02 on sc01.Snum=sc02.Snum) aa on student.Snum=aa.Snum;
 
#1.2、存在"01"课程但可能不存在"02"课程的情况(不存在时显示为null)(以下存在相同内容时不再解释)
select * from student right join (select sc01.Snum,Sc01.Cnum cnum1,sc01.score score1,sc02.cnum cnum2,sc02.score score2
from (select * from sc where cnum='01') sc01
 left join (select * from sc where cnum='02') sc02 on sc01.Snum=sc02.Snum) aa on student.Snum=aa.Snum;
 
select * from student inner join 
(select * from(select score from sc where cnum='01') a

select score from sc where cnum='01'
select score from sc where cnum='02'

select * from (select * from sc where cnum='01') sc01
inner join (select * from sc where cnum='02') sc02 on sc01.snum=sc02.snum
inner join
(select * from sc where cnum='02') b on a.snum=b.snum) c on student.Snum=c.snum;


select student.*,sc.Cnum,sc.score,sc02.Cnum,sc02.score from student left join
sc on sc.snum=student.snum and sc.Cnum='01'
inner join sc sc02 on sc02.snum=student.snum and sc02.Cnum='02'

select *,avg(score) as '平均成绩' from student s inner join 
sc on s.snum=sc.snum group by sc.snum


#1、查询"01"课程比"02"课程成绩高的学生的信息及课程分数
#1.1、查询同时存在"01"课程和"02"课程的情况
#1.2、存在"01"课程但可能不存在"02"课程的情况(不存在时显示为null)(以下存在相同内容时不再解释)
select * from student s inner join
sc sc01 on sc01.Snum=s.Snum and sc01.Cnum='01'
inner join sc sc02 on sc02.Snum=s.Snum and sc02.Cnum='02'
where sc01.score>sc02.score


#视图  创建视图 试图一般用于查看
create view myview as();

#函数
drop function if exists myadd;
delimiter //
create function myadd(a int,b int)
returns int
begin
	declare c int default 0;
    set c=a+b;
    return c;
end
//
delimiter ;

select myadd(2,3)

#6、查询"李"姓老师的数量
select count(Tname) from teacher where Tname like '李%' group by Tnum 


#8、查询没学过"张三"老师授课的同学的信息 

select * from student
select * from teacher
select * from sc
#1 哪些同学学了哪些课
select * from sc where Cnum=01
create view myview as(select * from sc where Cnum=01)

select * from student s left join myview m on s.Snum=m.Snum where ifnull(m.snum,0)=0

drop view myview
#9、查询学过编号为"01"并且也学过编号为"02"的课程的同学的信息
#11、查询没有学全所有课程的同学的信息 
select * from sc sc01 
inner join  sc sc02 on sc01.snum=sc02.snum and sc02.cnum='02' and sc01.cnum='01'
inner join sc sc03 on sc02.snum=sc03.snum and sc03.cnum='03'

select * from student s where Snum not in(
select sc01.snum from sc sc01 
inner join  sc sc02 on sc01.snum=sc02.snum and sc02.cnum='02' and sc01.cnum='01'
inner join sc sc03 on sc02.snum=sc03.snum and sc03.cnum='03'
)  

select * from sc where sc='03';
select * from sc
#12、查询至少有一门课与学号为"01"的同学所学相同的同学的信息 
select * from sc where sc.snum='01'
select student.* from student,sc where student.snum=sc.snum and cnum in(
select cnum from sc where snum=01
)group by snum



#13、查询和"01"号的同学学习的课程完全相同的其他同学的信息 XX

select * from student,sc where student.snum=sc.snum and cnum not in(
select cnum from sc where snum=01
)group by snum

select count(cnum) from sc where snum='01';

select snum,count(cnum) from sc group by snum 


select snum,count(cnum) from sc where 
cnum in(select cnum from sc where snum='01') group by snum





#14、查询没学过"张三"老师讲授的任一门课程的学生姓名 



#15、查询两门及其以上不及格课程的同学的学号，姓名及其平均成绩 





#存储过程
drop procedure if exists sele
delimiter //
create procedure sele()
begin

	select * from student;

end
//
delimiter ;
call sele

#题目
drop function if exists myfun
1 1 2 3 5 7 
delimiter //
create function myfun(smonth int)
returns INT
begin
declare i int default 3;
declare counts1 int default 1;
declare counts2 int default 1;
declare counts int default 1;
while i<=smonth and smonth>2 do
set counts=counts2+counts1;
set counts1=counts2;
set counts2=counts;
set i=i+1;
end while;
return counts;
end
//
delimiter ;
select myfun(10);
#条件
delimiter //
create function te(a int)
returns varchar(10)
begin
   declare b varchar default '';
   if a>


end
//
delimiter ;

#16、检索"01"课程分数小于60，按分数降序排列的学生信息
select s.*,sc01.score from student s inner join sc sc01
on sc01.cnum=01 and s.snum=sc01.snum where score<60 order by score desc

#17、按平均成绩从高到低显示所有学生的所有课程的成绩以及平均成绩
select s.*,(select score from sc sc01 where sc01.cnum=01 and s.snum=sc01.snum) sc01,
(select score from sc sc02 where sc02.cnum=02 and s.snum=sc02.snum) sc02,
(select score from sc sc03 where sc03.cnum=03 and s.snum=sc03.snum) sc03,
(select avg(score) from sc scavg group by snum having scavg.snum=s.snum) '平均成绩'
 from student s order by 平均成绩 desc


#18、查询各科成绩最高分、最低分和平均分：以如下形式显示：课程ID，课程name，最高分，最低分，平均分，及格率，中等率，优良率，优秀率
#及格为>=60，中等为：70-80，优良为：80-90，优秀为：>=90
create table sort(
	'排名' int primary key,
)


#19、按各科成绩进行排序，并显示排名
select *,(select count(*12)+1 from sc scp where scp.cnum=sc.cnum and scp.score>sc.score) pm from sc order by cnum asc,pm asc
 


select * from student
select * from sc

update student set snum=20 where snum=01;

delimiter //
create trigger up
after update
on student
for each row
begin
update sc set snum=new.Snum where snum=old.Snum;

end
//
delimiter ;
select * from t_file inner join t_user_file
on t_file.t_fileid=t_user_file.t_fileid
where t_user_file.t_userid= and t_file.t_filename=

use disk
select * from t_file
insert into t_file values(%lld,%s,%lld,%s,%s,%s,%d);

use disk
select * from t_user_file


select t_filename,t_filesize,t_fileuptt_user_filet_user_filet_user_fileime from t_file  inner join t_user_file on t_file.t_fileid = t_user_file.t_fileid  where t_userid =15046691258