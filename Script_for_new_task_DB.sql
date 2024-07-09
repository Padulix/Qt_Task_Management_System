create database task_management
go

use task_management

create table tasks
(
	task_id				varchar(255) primary key not null,
	task_description		varchar(50) not null,
	task_duration			int,			-- hours
	task_start_date			datetime,		-- date or time
	task_end_date			datetime,		-- date or time
	task_status			int not null,	-- 0 = not finished, 1 = in progress, 2 = finished
	task_comments			varchar(255)	-- comments
);

