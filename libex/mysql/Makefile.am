AUTOMAKE_OPTIONS= \
  foreign \
  subdir-objects
  
INCLUDES=-I../../include
  
lib_LTLIBRARIES=libmixmysql.la 
libmixmysql_la_SOURCES= \
  mysql_connection.cpp \
  mysql_creater.cpp \
  mysql_prepared_statement.cpp \
  mysql_result_set.cpp \
  mysql_statement.cpp

mixmysqldir=$(includedir)/mix/mysql
mixmysql_HEADERS=../../include/mix/mysql/mysql_connection.h \
  ../../include/mix/mysql/mysql_creater.h \
  ../../include/mix/mysql/mysql_prepared_statement.h \
  ../../include/mix/mysql/mysql_result_set.h \
  ../../include/mix/mysql/mysql_statement.h