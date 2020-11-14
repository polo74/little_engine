#include "db.hpp"

Db::Db(const char * path)
{
	if(sqlite3_open(path, &db))
	{
		fprintf(stdout, "ATTENTION : impossible d'ouvrir la base de données !!");
		return;
	}
}

Db::~Db()
{
	sqlite3_close(db);
}

