import MySQLdb

################################################
# @author Christoffer Holmstedt
# @date 2012-02-01 15:48
#
# MySQL class for ASAP access to the database
# Future improvement to project may include 
# switch some ORM library such as "Storm".
################################################
class MySQL:
    ######################################################
    # Constructor opens a connetion to the database.
    ######################################################
    def __init__ (self):
        self.conn = MySQLdb.connect (host = "localhost", user = "mulle", passwd = "mulle", db = "mulle", charset = "utf8", use_unicode = True)
        self.cursor = self.conn.cursor()
    
    ######################################################
    # Destructor closes all mysql connections that is open.
    ######################################################
    def __del__(self):
        self.cursor.close()
        self.conn.close()

    ######################################################
    # fetchAllData, fetches all available data in the 
    # "data" table.
    ######################################################
    def fetchAllData(self):
        returnValue = []
        self.cursor.execute ("SELECT id, type, value, datetime, host FROM data")
        while (1):
            row = self.cursor.fetchone()
            if row == None:
                break
            returnValue.append(row)
#            print "%s, %s, %s, %s, %s" % (row[0], row[1], row[2], row[3], row[4])
#        print "Number of rows returned: %d" % self.cursor.rowcount
        return returnValue

    ######################################################
    # Test function to see if the 
    # class has loaded properly
    ######################################################
    def printValue(self):
        print "You have executed MySQL.printValue and it prints this text succesfully."


#################################################
# Test code to test the MySQL class during 
# development.
#################################################
A = MySQL()

## Simple test function to see that it's up and running.
A.printValue()

## TODO: Fetch the last row
## This is to be able to test the "Insert one row" function.

## TODO: Insert one row into database

## Test the fetchAllData function.
rows = A.fetchAllData()
for row in rows:
    # Print entire tuple (one row from the table in the database).
    print row
    # Print "one column" from the row.
    print row[0], row[1], row[2]
