USE Airline
GO

CREATE PROCEDURE main (@wantedVersion INT )
AS 
BEGIN
	DECLARE @currentVersion INT
	DECLARE @command VARCHAR(50)

	SELECT @currentVersion = version
	FROM CurrentVersion

	PRINT @currentVersion

	IF @wantedVersion = @currentVersion 
	BEGIN
		PRINT 'Version already in use'
		RETURN
	END

	IF @wantedVersion NOT IN (SELECT version FROM AllVersions) 
	BEGIN
		PRINT 'Version does not exist'
		RETURN
	END
	
	WHILE @currentVersion < @wantedVersion
	BEGIN
		SET @currentVersion = @currentVersion + 1
		SET @command = (SELECT do FROM AllVersions WHERE version = @currentVersion)
		EXEC @command
		PRINT @currentVersion
		PRINT @command
	END

	WHILE @currentVersion > @wantedVersion
	BEGIN
		SET @command = (SELECT undo FROM AllVersions WHERE version = @currentVersion)
		EXEC @command
		SET @currentVersion = @currentVersion - 1
		PRINT @currentVersion
		PRINT @command
	END

END
GO

EXEC main 21
