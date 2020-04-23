create procedure insertPilots (@noOfRows INT) as
begin
	declare @counter int = 0
	declare @name varchar(30) = 'Pilot'
	declare @nameI varchar(30)
	while @counter < @noOfRows
	begin
		set @nameI = @name +cast(@counter as varchar)
		insert into Pilot values
		(@counter+1,@nameI)
		set @counter = @counter+1
	end
end
go

create procedure insertFlight (@noOfRows INT) as
begin
	declare @counter int = 0
	declare @departure varchar(30) = 'Departure'
	declare @departureI varchar(30)
	declare @arrival varchar(30) = 'Arrival'
	declare @arrivalI varchar(30)
	while @counter < @noOfRows
	begin
		set @departureI = @departure + cast(@counter as varchar)
		set @arrivalI = @arrival + cast(@counter as varchar)
		insert into Flight values
		(@counter+1,(@counter+1)/2+1, @departureI, @arrivalI)
		set @counter = @counter+1
	end
end
go

create procedure insertBooking (@noOfRows INT) as
begin
	declare @counter int = 0
	declare @price int = 500
	while @counter < @noOfRows
	begin
		insert into Booking values
		(@counter+1, @counter+1, @price+@counter*2)
		set @counter = @counter+1
	end
end
go