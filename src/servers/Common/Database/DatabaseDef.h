#ifndef _DATABASEDEF_H
#define _DATABASEDEF_H

#include "src/libraries/sapphire/mysqlConnector/MySqlConnector.h"
#include <Common/Database/DbLoader.h>
#include <Common/Database/CharaDbConnection.h>
#include <Common/Database/DbWorkerPool.h>
#include <Common/Database/PreparedStatement.h>

extern Core::Db::DbWorkerPool< Core::Db::CharaDbConnection > g_charaDb;

#endif
