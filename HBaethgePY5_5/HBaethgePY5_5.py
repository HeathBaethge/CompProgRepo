import sqlite3 as sl

#create/connect to the database named my-test.db
con = sl.connect('my-test.db')

#Once you have a connection, you can create a Cursor object and call its execute() method to perform SQL commands
c = con.cursor()

#get the count of tables with the name
c.execute(''' SELECT count(name) FROM sqlite_master WHERE type='table' AND name='USER' ''')

#if the count is 1, then  table exists
if c.fetchone()[0]==1 :
    print('Table Exists.')
else :
    #does not exist, create
    print('Table does not exist')

    #create table with a primary key, name field of text, and an age field of integer
    with con:
        con.execute('''
        CREATE TABLE USER(
            id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
            name TEXT,
            age INTEGER
        );
        ''')

    #create sql to insert data into the table
    sql = 'INSERT INTO USER (id, name, age) values(?, ?, ?)'
    data = [
        (1, 'Alice', 21),
        (2, 'Bob', 22),
        (3, 'Chris', 23)
    ]

    #run sql query
    with con:
        con.executemany(sql, data)

#connect and read back data
with con:
    data = con.execute("SELECT * FROM USER WHERE age <= 22")
    for row in data:
        print(row)