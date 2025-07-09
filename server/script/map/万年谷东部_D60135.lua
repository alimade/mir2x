local addmon = require('map.addmonster')
local addMonCo = addmon.monGener( -- 万年谷东部_D60135
{
    {
        name = '蜈蚣',
        loc = {
            {x = 50, y = 50, w = 50, h = 50, count = 20, time = 600},
        }
    },
    {
        name = '蝴蝶虫',
        loc = {
            {x = 50, y = 50, w = 50, h = 50, count = 20, time = 600},
        }
    },
    {
        name = '跳跳蜂',
        loc = {
            {x = 50, y = 50, w = 50, h = 50, count = 20, time = 600},
        }
    },
    {
        name = '钳虫',
        loc = {
            {x = 50, y = 50, w = 50, h = 50, count = 20, time = 600},
        }
    },
    {
        name = '黑色恶蛆',
        loc = {
            {x = 50, y = 50, w = 50, h = 50, count = 20, time = 600},
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
