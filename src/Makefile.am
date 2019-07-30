AUTOMAKE_OPTIONS= \
  foreign \
  subdir-objects
  
INCLUDES=-I../include -I/home/stan/dependents/instantclient_11_2/sdk/include

bin_PROGRAMS=mix_mysql_persist_demo \
	mix_oracle_persist_demo 
	
mix_mysql_persist_demo_SOURCES= \
  mysql_persist_demo.cpp \
  User.cpp \
  User.h
mix_mysql_persist_demo_LDADD=../lib/libmixpersist.la ../libex/mysql/libmixmysql.la -lmysqlclient -lmysqlcppconn
mix_mysql_persist_demo_LDFLAGS=-pthread -L/usr/lib64/mysql
mix_mysql_persist_demo_CXXFLAGS=-std=c++0x

mix_oracle_persist_demo_SOURCES= \
  oracle_persist_demo.cpp \
  User.cpp \
  User.h
mix_oracle_persist_demo_LDADD=../lib/libmixpersist.la ../libex/oracle/libmixoracle.la -locci -lclntsh -lnnz11 -ldl
mix_oracle_persist_demo_LDFLAGS=-pthread -L/home/stan/dependents/instantclient_11_2
mix_oracle_persist_demo_CXXFLAGS=-std=c++0x
