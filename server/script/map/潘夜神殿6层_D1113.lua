local addmon = require('map.addmonster')
local addMonCo = addmon.monGener( -- 潘夜神殿6层_D1113
{
    {
        name = '潘夜云魔',
        loc = {
            {x = 200, y = 200, w = 200, h = 200, count = 50, time = 600},
        }
    },
    {
        name = '潘夜云魔0',
        loc = {
            {x = 200, y = 200, w = 200, h = 200, count = 1, time = 3600},
        }
    },
    {
        name = '潘夜云魔8',
        loc = {
            {x = 200, y = 200, w = 200, h = 200, count = 1, time = 3600},
        }
    },
    {
        name = '潘夜冰魔',
        loc = {
            {x = 200, y = 200, w = 200, h = 200, count = 50, time = 600},
        }
    },
    {
        name = '潘夜右护卫',
        loc = {
            {x = 200, y = 200, w = 200, h = 200, count = 75, time = 600},
        }
    },
    {
        name = '潘夜右护卫0',
        loc = {
            {x = 200, y = 200, w = 200, h = 200, count = 1, time = 3600},
        }
    },
    {
        name = '潘夜右护卫8',
        loc = {
            {x = 200, y = 200, w = 200, h = 200, count = 1, time = 3600},
        }
    },
    {
        name = '潘夜左护卫',
        loc = {
            {x = 200, y = 200, w = 200, h = 200, count = 75, time = 600},
        }
    },
    {
        name = '潘夜战士',
        loc = {
            {x = 200, y = 200, w = 200, h = 200, count = 50, time = 600},
        }
    },
    {
        name = '潘夜火魔',
        loc = {
            {x = 200, y = 200, w = 200, h = 200, count = 50, time = 600},
        }
    },
    {
        name = '潘夜风魔',
        loc = {
            {x = 200, y = 200, w = 200, h = 200, count = 50, time = 600},
        }
    },
    {
        name = '潘夜鬼将',
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
