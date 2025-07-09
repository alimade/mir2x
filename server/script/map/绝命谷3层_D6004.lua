local addmon = require('map.addmonster')
local addMonCo = addmon.monGener( -- 绝命谷3层_D6004
{
    {
        name = '蜈蚣',
        loc = {
            {x = 150, y = 150, w = 150, h = 150, count = 60, time = 600},
        }
    },
    {
        name = '蜈蚣0',
        loc = {
            {x = 150, y = 150, w = 140, h = 140, count = 1, time = 3600},
        }
    },
    {
        name = '蝴蝶虫',
        loc = {
            {x = 150, y = 150, w = 150, h = 150, count = 60, time = 600},
        }
    },
    {
        name = '蝴蝶虫0',
        loc = {
            {x = 150, y = 150, w = 140, h = 140, count = 1, time = 3600},
        }
    },
    {
        name = '跳跳蜂',
        loc = {
            {x = 150, y = 150, w = 150, h = 150, count = 60, time = 600},
        }
    },
    {
        name = '邪恶钳虫',
        loc = {
            {x = 150, y = 150, w = 150, h = 150, count = 2, time = 7200},
        }
    },
    {
        name = '钳虫',
        loc = {
            {x = 150, y = 150, w = 150, h = 150, count = 60, time = 600},
        }
    },
    {
        name = '钳虫0',
        loc = {
            {x = 150, y = 150, w = 140, h = 140, count = 1, time = 3600},
        }
    },
    {
        name = '黑色恶蛆',
        loc = {
            {x = 150, y = 150, w = 150, h = 150, count = 60, time = 600},
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
