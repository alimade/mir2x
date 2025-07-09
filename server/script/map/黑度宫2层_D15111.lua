local addmon = require('map.addmonster')
local addMonCo = addmon.monGener( -- 黑度宫2层_D15111
{
    {
        name = '地牢女神1',
        loc = {
            {x = 100, y = 100, w = 100, h = 100, count = 70, time = 600},
        }
    },
    {
        name = '地牢女神8',
        loc = {
            {x = 100, y = 100, w = 100, h = 100, count = 7, time = 600},
        }
    },
    {
        name = '火焰狮子',
        loc = {
            {x = 100, y = 100, w = 100, h = 100, count = 100, time = 600},
        }
    },
    {
        name = '火焰狮子8',
        loc = {
            {x = 100, y = 100, w = 100, h = 100, count = 10, time = 600},
        }
    },
    {
        name = '石像狮子',
        loc = {
            {x = 100, y = 100, w = 100, h = 100, count = 30, time = 600},
        }
    },
    {
        name = '石像狮子8',
        loc = {
            {x = 100, y = 100, w = 100, h = 100, count = 3, time = 600},
        }
    },
    {
        name = '震天首将',
        loc = {
            {x = 100, y = 100, w = 90, h = 90, count = 1, time = 7200},
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
