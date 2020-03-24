CREATE TABLE [dbo].[Table3]
(
	[Id] INT NOT NULL PRIMARY KEY, 
    [type] NVARCHAR(50) NULL, 
    [min] FLOAT NULL, 
    [max] FLOAT NULL, 
    [sd] FLOAT NULL, 
    [details] NVARCHAR(50) NULL, 
    [o] INT NULL, 
    [name] NVARCHAR(50) NULL, 
    [createdBy] NVARCHAR(50) NULL, 
    [createdAt] TIME NULL, 
    [sample] NVARCHAR(50) NULL, 
    [mean] FLOAT NULL, 
    [article] NVARCHAR(50) NULL
)
