local tp = {}

function tp.uidReqSpaceMove(uid, mapName, x, y, gold, level)
    gold  = argDefault(gold,  0)
    level = argDefault(level, 0)

    assertType(gold, 'integer')
    assertType(level, 'integer')

    if gold > 0 and gold > uidQueryGold(uid) then
        uidPostXML(uid,
        [[
            <layout>
                <par>你没有%d金币！</par>
                <par><event id="%s">关闭</event></par>
            </layout>
        ]], gold, SYS_EXIT)
        return
    end

    if level > 0 and level > uidQueryLevel(uid) then
        uidPostXML(uid,
        [[
            <layout>
                <par>你还没达到%d级！</par>
                <par><event id="%s">关闭</event></par>
            </layout>
        ]], level, SYS_EXIT)
        return
    end

    if uidSpaceMove(uid, mapName, x, y) then
        if gold > 0 then
            uidRemoveGold(uid, gold)
        end
    end
end

-- setup the teleport interface
-- sample:
--
-- tp.setTeleport({
--     {name = '比奇城', map = '比奇县_0', x = 447, y = 386, gold = 10},
--     {map = '沙巴克城_3', x = 216, y = 148, gold = 50, level = 3},
--     {}
--     {map = '银杏山谷_02', x = 246, y = 200, gold = 25, level = 2},
-- })
--
function tp.setTeleport(titlePar, dst)
    if processNPCEvent ~= nil then
        fatalPrintf('processNPCEvent has already been defined')
    end

    if type(titlePar) ~= 'string' then
        fatalPrintf('expect an XML paragraph string, get %s', type(titlePar))
    end

    if type(dst) ~= 'table' then
        fatalPrintf('invalid argument: dst:%s', type(dst))
    end

    local dstParList = {}
    local processHandle = {}

    for i, d in ipairs(dst) do
        if type(d) ~= 'table' then
            fatalPrintf('expect table entry, get %s', type(d))
        else
            if tableSize(d) == 0 then
                table.insert(dstParList, '<par></par>')
            else
                if type(d.map) ~= 'string' then
                    addLog(LOGTYPE_WARNING, 'ignore invalid map: npc = %s', getNPCName())
                elseif type(d.x) ~= 'number' or type(d.y) ~= 'number' then
                    addLog(LOGTYPE_WARNING, 'ignore invalid map location: npc = %s, map = %s', getNPCName(), d.map)
                else
                    local gold = argDefault(d.gold, 0)
                    local level = argDefault(d.level, 0)
                    local gotoTag = string.format('tp_goto_%d::%s', i, SYS_EXIT)

                    local mapName = ''
                    if d.name ~= nil then
                        if type(d.name) == 'string' then
                            mapName = d.name
                        else
                            fatalPrintf('invalid argument: d.name has type %s', type(d.name))
                        end
                    else
                        local startPos = string.find(d.map, '_')
                        if startPos ~= nil then
                            mapName = string.sub(d.map, 1, startPos - 1)
                        else
                            mapName = d.map
                        end
                    end

                    if gold > 0 and level > 0 then
                        table.insert(dstParList, string.format('<par><event id="%s" close="1">%s（金币%d，等级%d）</event></par>', gotoTag, mapName, gold, level))
                    elseif gold > 0 then
                        table.insert(dstParList, string.format('<par><event id="%s" close="1">%s（金币%d）</event></par>', gotoTag, mapName, gold))
                    elseif level > 0 then
                        table.insert(dstParList, string.format('<par><event id="%s" close="1">%s（等级%d）</event></par>', gotoTag, mapName, level))
                    else
                        table.insert(dstParList, string.format('<par><event id="%s" close="1">%s</event></par>', gotoTag, mapName))
                    end

                    processHandle[gotoTag] = function(uid, value)
                        tp.uidReqSpaceMove(uid, d.map, d.x, d.y, gold, level)
                    end
                end
            end
        end
    end

    if tableSize(dstParList) == 0 then
        fatalPrintf('no valid destination specified in the argument list')
    end

    processHandle[SYS_ENTER] = function(uid, value)
        uidPostXML(uid,
        [[
            <layout>
                %s
                <par></par>
                %s
                <par><event id="%s">关闭</event></par>
            </layout>
        ]], titlePar, table.concat(dstParList), SYS_EXIT)
    end
    setEventHandler(processHandle)
end

return tp
