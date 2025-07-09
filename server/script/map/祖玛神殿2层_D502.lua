local addmon = require('map.addmonster')
local addMonCo = addmon.monGener( -- 祖玛神殿2层_D502
{
    {
        name = '大老鼠',
        loc = {
            {x = 200, y = 200, w = 200, h = 200, count = 195, time = 600},
        }
    },
    {
        name = '大老鼠0',
        loc = {
            {x = 200, y = 200, w = 200, h = 200, count = 1, time = 3600},
        }
    },
    {
        name = '大老鼠8',
        loc = {
            {x = 200, y = 200, w = 200, h = 200, count = 1, time = 3600},
        }
    },
    {
        name = '楔蛾',
        loc = {
            {x = 200, y = 200, w = 200, h = 200, count = 155, time = 600},
        }
    },
    {
        name = '祖玛弓箭手',
        loc = {
            {x = 200, y = 200, w = 200, h = 200, count = 135, time = 600},
        }
    },
    {
        name = '祖玛弓箭手0',
        loc = {
            {x = 200, y = 200, w = 200, h = 200, count = 2, time = 3600},
        }
    },
    {
        name = '祖玛弓箭手8',
        loc = {
            {x = 200, y = 200, w = 200, h = 200, count = 2, time = 3600},
        }
    },
    {
        name = '角蝇',
        loc = {
            {x = 200, y = 200, w = 200, h = 200, count = 50, time = 600},
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
