local addmon = require('map.addmonster')
local addMonCo = addmon.monGener( -- 真天宫东馆3层_D15033
{
    {
        name = '武力神将',
        loc = {
            {x = 150, y = 150, w = 140, h = 140, count = 160, time = 600},
        }
    },
    {
        name = '武力神将8',
        loc = {
            {x = 150, y = 150, w = 140, h = 140, count = 16, time = 600},
        }
    },
    {
        name = '火焰狮子',
        loc = {
            {x = 150, y = 150, w = 140, h = 140, count = 125, time = 600},
        }
    },
    {
        name = '火焰狮子8',
        loc = {
            {x = 150, y = 150, w = 140, h = 140, count = 12, time = 600},
        }
    },
    {
        name = '石像狮子',
        loc = {
            {x = 150, y = 150, w = 140, h = 140, count = 125, time = 600},
        }
    },
    {
        name = '石像狮子8',
        loc = {
            {x = 150, y = 150, w = 140, h = 140, count = 15, time = 600},
        }
    },
    {
        name = '震天首将',
        loc = {
            {x = 150, y = 150, w = 140, h = 140, count = 1, time = 7200},
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
