local addmon = require('map.addmonster')
local addMonCo = addmon.monGener( -- 天然洞穴1层_D011
{
    {
        name = '洞蛆',
        loc = {
            {x = 200, y = 200, w = 190, h = 190, count = 150, time = 600},
        }
    },
    {
        name = '蝎子',
        loc = {
            {x = 200, y = 200, w = 190, h = 190, count = 150, time = 600},
        }
    },
    {
        name = '骷髅',
        loc = {
            {x = 200, y = 200, w = 190, h = 190, count = 150, time = 600},
        }
    },
    {
        name = '骷髅0',
        loc = {
            {x = 200, y = 200, w = 190, h = 190, count = 2, time = 3600},
        }
    },
    {
        name = '骷髅战士',
        loc = {
            {x = 200, y = 200, w = 190, h = 190, count = 150, time = 600},
        }
    },
    {
        name = '骷髅战士0',
        loc = {
            {x = 200, y = 200, w = 190, h = 190, count = 2, time = 3600},
        }
    },
    {
        name = '骷髅精灵',
        loc = {
            {x = 200, y = 200, w = 190, h = 190, count = 1, time = 7200},
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
