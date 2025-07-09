local addmon = require('map.addmonster')
local addMonCo = addmon.monGener( -- 沙漠_6
{
    {
        name = '夜行鬼09',
        loc = {
            {x = 400, y = 400, w = 400, h = 400, count = 200, time = 1200},
        }
    },
    {
        name = '诺玛大法老',
        loc = {
            {x = 400, y = 400, w = 390, h = 390, count = 4, time = 7200},
        }
    },
    {
        name = '异界之门',
        loc = {
            {x = 277, y = 319, w = 10, h = 10, count = 1, time = 2880000},
        }
    },
    {
        name = '沙漠树魔',
        loc = {
            {x = 400, y = 400, w = 380, h = 380, count = 200, time = 600},
        }
    },
    {
        name = '沙漠石人',
        loc = {
            {x = 400, y = 400, w = 380, h = 380, count = 600, time = 600},
        }
    },
    {
        name = '沙漠石人0',
        loc = {
            {x = 400, y = 400, w = 380, h = 380, count = 1, time = 3600},
        }
    },
    {
        name = '沙漠树魔0',
        loc = {
            {x = 400, y = 400, w = 380, h = 380, count = 1, time = 3600},
        }
    },
    {
        name = '诺玛0',
        loc = {
            {x = 400, y = 400, w = 380, h = 380, count = 700, time = 600},
        }
    },
    {
        name = '诺玛1',
        loc = {
            {x = 400, y = 400, w = 380, h = 380, count = 700, time = 600},
        }
    },
    {
        name = '诺玛10',
        loc = {
            {x = 400, y = 400, w = 380, h = 380, count = 1, time = 3600},
        }
    },
    {
        name = '诺玛将士',
        loc = {
            {x = 400, y = 400, w = 380, h = 380, count = 700, time = 600},
        }
    },
    {
        name = '诺玛将士0',
        loc = {
            {x = 400, y = 400, w = 380, h = 380, count = 1, time = 3600},
        }
    },
    {
        name = '诺玛教主2',
        loc = {
            {x = 400, y = 400, w = 390, h = 390, count = 1, time = 7200},
        }
    },
    {
        name = '诺玛法老',
        loc = {
            {x = 400, y = 400, w = 380, h = 380, count = 600, time = 600},
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
