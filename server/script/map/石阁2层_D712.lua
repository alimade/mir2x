local addmon = require('map.addmonster')
local addMonCo = addmon.monGener( -- 石阁2层_D712
{
    {
        name = '楔蛾',
        loc = {
            {x = 200, y = 200, w = 200, h = 200, count = 205, time = 600},
        }
    },
    {
        name = '白野猪',
        loc = {
            {x = 200, y = 200, w = 200, h = 200, count = 1, time = 7200},
        }
    },
    {
        name = '红野猪',
        loc = {
            {x = 200, y = 200, w = 200, h = 200, count = 225, time = 600},
        }
    },
    {
        name = '红野猪0',
        loc = {
            {x = 200, y = 200, w = 200, h = 200, count = 3, time = 3600},
        }
    },
    {
        name = '黑野猪',
        loc = {
            {x = 200, y = 200, w = 200, h = 200, count = 243, time = 600},
        }
    },
    {
        name = '黑野猪0',
        loc = {
            {x = 200, y = 200, w = 200, h = 200, count = 3, time = 3600},
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
