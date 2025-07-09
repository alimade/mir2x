local addmon = require('map.addmonster')
local addMonCo = addmon.monGener( -- 潘夜石窟3层_D1213
{
    {
        name = '骨鬼将',
        loc = {
            {x = 150, y = 150, w = 140, h = 140, count = 1, time = 7200},
        }
    },
    {
        name = '骷髅士兵',
        loc = {
            {x = 150, y = 150, w = 150, h = 150, count = 120, time = 600},
        }
    },
    {
        name = '骷髅士兵0',
        loc = {
            {x = 150, y = 150, w = 150, h = 150, count = 1, time = 3600},
        }
    },
    {
        name = '骷髅弓箭手',
        loc = {
            {x = 150, y = 150, w = 150, h = 150, count = 120, time = 600},
        }
    },
    {
        name = '骷髅弓箭手0',
        loc = {
            {x = 150, y = 150, w = 150, h = 150, count = 1, time = 3600},
        }
    },
    {
        name = '骷髅武士',
        loc = {
            {x = 150, y = 150, w = 150, h = 150, count = 120, time = 600},
        }
    },
    {
        name = '骷髅武将',
        loc = {
            {x = 150, y = 150, w = 150, h = 150, count = 120, time = 600},
        }
    },
    {
        name = '骷髅武将0',
        loc = {
            {x = 150, y = 150, w = 150, h = 150, count = 1, time = 3600},
        }
    },
})

function main()
    while true do
        local rc, errMsg = coroutine.resume(addMonCo)
        if not rc then
            fatalPrintf('addMonCo failed: %s', argDefault(errMsg, 'unknown error'))
        end
        pause(1000 * 5)
    end
end
