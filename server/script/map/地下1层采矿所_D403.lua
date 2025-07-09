local addmon = require('map.addmonster')
local addMonCo = addmon.monGener( -- 地下1层采矿所_D403
{
    {
        name = '僧侣僵尸',
        loc = {
            {x = 100, y = 100, w = 100, h = 100, count = 3, time = 600},
        }
    },
    {
        name = '僵尸1',
        loc = {
            {x = 100, y = 100, w = 100, h = 100, count = 33, time = 600},
        }
    },
    {
        name = '僧侣僵尸',
        loc = {
            {x = 100, y = 100, w = 100, h = 100, count = 33, time = 600},
        }
    },
    {
        name = '僵尸3',
        loc = {
            {x = 100, y = 100, w = 100, h = 100, count = 33, time = 600},
        }
    },
    {
        name = '僵尸30',
        loc = {
            {x = 100, y = 100, w = 100, h = 100, count = 1, time = 3600},
        }
    },
    {
        name = '僵尸4',
        loc = {
            {x = 100, y = 100, w = 100, h = 100, count = 33, time = 600},
        }
    },
    {
        name = '僵尸40',
        loc = {
            {x = 100, y = 100, w = 100, h = 100, count = 1, time = 3600},
        }
    },
    {
        name = '僵尸5',
        loc = {
            {x = 100, y = 100, w = 100, h = 100, count = 33, time = 600},
        }
    },
    {
        name = '僵尸50',
        loc = {
            {x = 100, y = 100, w = 100, h = 100, count = 1, time = 3600},
        }
    },
    {
        name = '尸王',
        loc = {
            {x = 100, y = 100, w = 90, h = 90, count = 1, time = 7200},
        }
    },
    {
        name = '洞蛆',
        loc = {
            {x = 100, y = 100, w = 100, h = 100, count = 33, time = 600},
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
