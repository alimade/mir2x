local addmon = require('map.addmonster')
local addMonCo = addmon.monGener( -- 诺玛勇士墓穴_D1606
{
    {
        name = '诺玛司令',
        loc = {
            {x = 23, y = 26, w = 50, h = 50, count = 8, time = 1800},
        }
    },
    {
        name = '诺玛抛石兵',
        loc = {
            {x = 23, y = 26, w = 50, h = 50, count = 8, time = 1800},
        }
    },
    {
        name = '诺玛教主',
        loc = {
            {x = 31, y = 41, w = 1, h = 1, count = 1, time = 14400},
        }
    },
    {
        name = '诺玛斧兵',
        loc = {
            {x = 23, y = 26, w = 50, h = 50, count = 8, time = 1800},
        }
    },
    {
        name = '诺玛装甲兵',
        loc = {
            {x = 23, y = 26, w = 50, h = 50, count = 8, time = 1800},
        }
    },
    {
        name = '诺玛骑兵',
        loc = {
            {x = 23, y = 26, w = 50, h = 50, count = 8, time = 1800},
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
