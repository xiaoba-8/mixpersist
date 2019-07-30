AUTOMAKE_OPTIONS= \
  foreign \
  subdir-objects
  
INCLUDES=-I../../include -I/home/stan/dependents/instantclient_11_2/sdk/include
  
lib_LTLIBRARIES=libmixoracle.la 
libmixoracle_la_SOURCES= \
  oracle_connection.cpp \
  oracle_creater.cpp \
  oracle_result_set.cpp \
  oracle_statement.cpp

mixoracledir=$(includedir)/mix/oracle
mixoracle_HEADERS=../../include/mix/oracle/oracle_connection.h \
  ../../include/mix/oracle/i_ora_creater.h \
  ../../include/mix/oracle/oracle_statement.h \
  ../../include/mix/oracle/oracle_result_set.h \
  ../../include/mix/oracle/oracle_creater.h