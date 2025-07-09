#include "uidf.hpp"
#include "mathf.hpp"
#include "dbpod.hpp"
#include "dbcomid.hpp"
#include "mapbindb.hpp"
#include "actorpool.hpp"
#include "server.hpp"
#include "serverargparser.hpp"
#include "serverluamodule.hpp"
#include "serverconfigurewindow.hpp"

extern DBPod *g_dbPod;
extern MapBinDB *g_mapBinDB;
extern ActorPool *g_actorPool;
extern Server *g_server;
extern ServerArgParser *g_serverArgParser;
extern ServerConfigureWindow *g_serverConfigureWindow;

ServerLuaModule::ServerLuaModule()
    : LuaModule()
{
    pfrCheck(execString(
            R"###( g_serverArgParser = rotable({    )###"
            R"###(     disableMapScript    = %s,    )###"
            R"###(     disablePetSpawn     = %s,    )###"
            R"###(     disableGuardSpawn   = %s,    )###"
            R"###(     disableMonsterSpawn = %s,    )###"
            R"###(     disableNPCSpawn     = %s,    )###"
            R"###( })                               )###",

            to_boolcstr(g_serverArgParser->sharedConfig().disableMapScript   ),
            to_boolcstr(g_serverArgParser->sharedConfig().disablePetSpawn    ),
            to_boolcstr(g_serverArgParser->sharedConfig().disableGuardSpawn  ),
            to_boolcstr(g_serverArgParser->sharedConfig().disableMonsterSpawn),
            to_boolcstr(g_serverArgParser->sharedConfig().disableNPCSpawn    )));

    pfrCheck(execString("package.path = package.path .. ';%s/?.lua'", []() -> std::string
    {
        if(const auto cfgScriptPath = g_serverArgParser->slave ? std::string{} : g_serverConfigureWindow->getConfig().scriptPath; cfgScriptPath.empty()){
            return "script";
        }
        else{
            return cfgScriptPath;
        }
    }().c_str()));

    bindFunction("uidAlive", [](uint64_t uid)
    {
        return g_actorPool->checkUIDValid(uid);
    });

    bindFunction("getServiceCoreUID", []() -> uint64_t
    {
        return uidf::getServiceCoreUID();
    });

    bindFunction("randMapGLoc", [](std::string mapName)
    {
        const auto fnGetRandGLoc = [](const auto dataCPtr) -> std::array<int, 2>
        {
            while(true){
                const int x = mathf::rand() % dataCPtr->w();
                const int y = mathf::rand() % dataCPtr->h();

                if(dataCPtr->validC(x, y) && dataCPtr->cell(x, y).land.canThrough()){
                    return {x, y};
                }
            }
            throw fflreach();
        };

        if(const auto mapID = DBCOM_MAPID(to_u8cstr(mapName))){
            if(const auto dataCPtr = g_mapBinDB->retrieve(mapID)){
                return sol::as_returns(fnGetRandGLoc(dataCPtr));
            }
            else{
                throw fflerror("map %s has no valid mir2x data", to_cstr(mapName));
            }
        }
        else{
            throw fflerror("invalid map name: %s", to_cstr(mapName));
        }
    });

    bindFunction("hasDatabase", [](std::string dbName) -> bool
    {
        fflassert(!dbName.empty());
        return g_dbPod->createQuery(u8R"###(select name from sqlite_master where type='table' and name='%s')###", to_cstr(dbName)).executeStep();
    });

    bindFunction("dbExecString", [](std::string cmd)
    {
        fflassert(!cmd.empty());
        g_dbPod->exec("%s", to_cstr(cmd));
    });

    bindFunction("dbQueryString", [](std::string query, sol::this_state s)
    {
        fflassert(!query.empty());
        auto queryStatement = g_dbPod->createQuery(to_cstr(query));

        sol::state_view sv(s);
        std::vector<std::map<std::string, sol::object>> queryResult;

        queryResult.reserve(8);
        while(queryStatement.executeStep()){
            std::map<std::string, sol::object> rowResult;
            for(int i = 0; i < queryStatement.getColumnCount(); ++i){
                switch(const auto column = queryStatement.getColumn(i); column.getType()){
                    case SQLITE_INTEGER:
                        {
                            rowResult[column.getName()] = sol::object(sv, sol::in_place_type<int>, column.getInt());
                            break;
                        }
                    case SQLITE_FLOAT:
                        {
                            rowResult[column.getName()] = sol::object(sv, sol::in_place_type<double>, column.getDouble());
                            break;
                        }
                    case SQLITE_TEXT:
                        {
                            rowResult[column.getName()] = sol::object(sv, sol::in_place_type<std::string>, column.getText());
                            break;
                        }
                    default:
                        {
                            throw fflerror("column type not supported: %d", column.getType());
                        }
                }
            }

            if(rowResult.size() != to_uz(queryStatement.getColumnCount())){
                throw fflerror("failed to parse query result row: missing column");
            }
            queryResult.push_back(std::move(rowResult));
        }
        return sol::nested<decltype(queryResult)>(std::move(queryResult));
    });

    pfrCheck(execRawString(BEGIN_LUAINC(char)
#include "serverluamodule.lua"
    END_LUAINC()));
}

void ServerLuaModule::addLogString(int logType, const char8_t *logInfo)
{
    // any time if you call addLog() or addLogString() in lua module
    // this will get printed in the server GUI console

    switch(logType){
        case 0 : g_server->addLog(LOGTYPE_INFO   , "%s", to_cstr(logInfo)); return;
        case 1 : g_server->addLog(LOGTYPE_WARNING, "%s", to_cstr(logInfo)); return;
        default: g_server->addLog(LOGTYPE_FATAL  , "%s", to_cstr(logInfo)); return;
    }
}
