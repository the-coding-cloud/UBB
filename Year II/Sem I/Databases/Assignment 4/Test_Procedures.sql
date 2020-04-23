INSERT INTO Tables(Name) VALUES ('Pilot'), ('Flight'), ('Booking')
INSERT INTO Views(Name) VALUES ('View1'),('View2'),('View3')
INSERT INTO Tests(Name) VALUES ('Test1000'),('Test5000'),('Test10000')

SELECT * FROM Tables
SELECT * FROM Views
SELECT * FROM Tests

INSERT INTO TestTables VALUES (1,1,1000,1),(1,2,1000,2),(1,3,1000,3)
INSERT INTO TestTables VALUES (2,1,5000,1),(2,2,5000,2),(2,3,5000,3)
INSERT INTO TestViews VALUES (1,1),(1,2),(1,3)
INSERT INTO TestViews VALUES (2,1),(2,2),(2,3)
GO

CREATE PROCEDURE RunTest (@testNumber INT) AS
BEGIN
	DECLARE @startTimeDelete DATETIME
    DECLARE @endTimeDelete DATETIME

	SET @startTimeDelete = GETDATE()
	EXEC deleteBooking
	SET @endTimeDelete = GETDATE()
	INSERT INTO TestRuns VALUES('delete', @startTimeDelete, @endTimeDelete)
	INSERT INTO TestRunTables VALUES (@@IDENTITY, 3, @startTimeDelete, @endTimeDelete)

	SET @startTimeDelete = GETDATE()
	EXEC deleteFlight
	SET @endTimeDelete = GETDATE()
	INSERT INTO TestRuns VALUES('delete', @startTimeDelete, @endTimeDelete)
	INSERT INTO TestRunTables VALUES (@@IDENTITY, 2, @startTimeDelete, @endTimeDelete)

	SET @startTimeDelete = GETDATE()
	EXEC deletePilot
	SET @endTimeDelete = GETDATE()
	INSERT INTO TestRuns VALUES('delete', @startTimeDelete, @endTimeDelete)
	INSERT INTO TestRunTables VALUES (@@IDENTITY, 1, @startTimeDelete, @endTimeDelete)

	DECLARE @noOfRows INT
	SELECT TOP 1 @noOfRows = NoOfRows
	FROM TestTables
	WHERE TestID = @testNumber

	DECLARE @startTimeInsert DATETIME
    DECLARE @endTimeInsert DATETIME

	SET @startTimeInsert = GETDATE()
	EXEC insertPilots @noOfRows
	SET @endTimeInsert = GETDATE()
	INSERT INTO TestRuns VALUES('insert', @startTimeInsert, @endTimeInsert)
	INSERT INTO TestRunTables VALUES (@@IDENTITY, 1, @startTimeInsert, @endTimeInsert)

	SET @startTimeInsert = GETDATE()
	EXEC insertFlight @noOfRows
	SET @endTimeInsert = GETDATE()
	INSERT INTO TestRuns VALUES('insert', @startTimeInsert, @endTimeInsert)
	INSERT INTO TestRunTables VALUES (@@IDENTITY, 2, @startTimeInsert, @endTimeInsert)

	SET @startTimeInsert = GETDATE()
	EXEC insertBooking @noOfRows
	SET @endTimeInsert = GETDATE()
	INSERT INTO TestRuns VALUES('insert', @startTimeInsert, @endTimeInsert)
	INSERT INTO TestRunTables VALUES (@@IDENTITY, 3, @startTimeInsert, @endTimeInsert)

	DECLARE @startTimeView DATETIME
    DECLARE @endTimeView DATETIME

	SET @startTimeView = GETDATE()
	EXEC View_1
	SET @endTimeView = GETDATE()
	INSERT INTO TestRuns VALUES('view', @startTimeView, @endTimeView)
	INSERT INTO TestRunViews VALUES (@@IDENTITY, 1, @startTimeView, @endTimeView)

	SET @startTimeView = GETDATE()
	EXEC View_2
	SET @endTimeView = GETDATE()
	INSERT INTO TestRuns VALUES('view', @startTimeView, @endTimeView)
	INSERT INTO TestRunViews VALUES (@@IDENTITY, 2, @startTimeView, @endTimeView)

	SET @startTimeView = GETDATE()
	EXEC View_3
	SET @endTimeView = GETDATE()
	INSERT INTO TestRuns VALUES('view', @startTimeView, @endTimeView)
	INSERT INTO TestRunViews VALUES (@@IDENTITY, 3, @startTimeView, @endTimeView)
END
GO

SET NOCOUNT ON
EXEC RunTest 1

SELECT * FROM TestRuns
SELECT * FROM TestRunTables
SELECT * FROM TestRunViews