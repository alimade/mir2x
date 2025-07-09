local addmon = require('map.addmonster')
local addMonCo = addmon.monGener( -- 石阁7层_D717
{
    {
        name = '楔蛾',
        loc = {
            {x = 0, y = 0, w = 100, h = 100, count = 25, time = 600},
        }
    },
    {
        name = '白野猪',
        loc = {
            {x = 0, y = 0, w = 100, h = 100, count = 2, time = 7200},
        }
    },
    {
        name = '红野猪',
        loc = {
            {x = 0, y = 0, w = 100, h = 100, count = 25, time = 600},
            {x = 0, y = 0, w = 100, h = 100, count = 25, time = 600},
        }
    },
    {
        name = '蝎蛇',
        loc = {
            {x = 0, y = 0, w = 100, h = 100, count = 25, time = 600},
            {x = 0, y = 0, w = 100, h = 100, count = 25, time = 600},
        }
    },
    {
        name = '角蝇',
        loc = {
            {x = 0, y = 0, w = 100, h = 100, count = 25, time = 600},
        }
    },
    {
        name = '邪恶毒蛇',
        loc = {
            {x = 0, y = 0, w = 100, h = 100, count = 1, time = 7200},
        }
    },
    {
        name = '黑野猪',
        loc = {
            {x = 0, y = 0, w = 100, h = 100, count = 25, time = 600},
            {x = 0, y = 0, w = 100, h = 100, count = 25, time = 600},
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
