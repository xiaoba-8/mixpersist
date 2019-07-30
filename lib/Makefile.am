AUTOMAKE_OPTIONS= \
  foreign \
  subdir-objects
  
INCLUDES=-I../include
  
lib_LTLIBRARIES=libmixpersist.la 
libmixpersist_la_SOURCES= \
  mix/database/database_factory.cpp \
  mix/database/dbdatas.cpp \
  mix/database/i_prepared_statement.cpp \
  mix/database/i_result_set.cpp \
  mix/database/sql_exception.cpp \
  mix/database/transaction_manager.cpp \
  mix/database/db_mutex.cpp \
  mix/database/GUIDGenerator.cpp \
  mix/database/time-tzset.c \
  mix/database/time-tzset.h \
  mix/persist/dao_helper.cpp \
  mix/persist/persist.cpp
libmixpersist_la_CXXFLAGS=-std=c++0x

mixdatabasedir=$(includedir)/mix/database
mixdatabase_HEADERS=../include/mix/database/any_ptr.h \
  ../include/mix/database/database_factory.h \
  ../include/mix/database/dbdatas.h \
  ../include/mix/database/dbmapping.h \
  ../include/mix/database/GUIDGenerator.h \
  ../include/mix/database/i_connection.h \
  ../include/mix/database/i_creater.h \
  ../include/mix/database/i_prepared_statement.h \
  ../include/mix/database/i_result_set.h \
  ../include/mix/database/i_statement.h \
  ../include/mix/database/idbc.h \
  ../include/mix/database/sql_exception.h \
  ../include/mix/database/transaction_manager.h 

mixpersistdir=$(includedir)/mix/persist
mixpersist_HEADERS=../include/mix/persist/dao_helper.h \
  ../include/mix/persist/persist.hpp
  