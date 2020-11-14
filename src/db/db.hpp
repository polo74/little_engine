#ifndef DB_HPP
#define DB_HPP

#include <sqlite3.h>
#include <cstdio>

class Db
{
	public:
		Db(const char *);
		~Db();
	protected:
		virtual int create() = 0;
		virtual int insert() = 0;
	private:
		sqlite3 * db;
};

#endif
