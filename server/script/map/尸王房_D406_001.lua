local addmon = require('map.addmonster')
local addMonCo = addmon.monGener( -- 尸王房_D406_001
{
    {
        name = '尸王',
        loc = {
            {x = 15, y = 15, w = 5, h = 5, count = 1, time = 7200},
        }
    },
    {
        name = '尸王2',
        loc = {
            {x = 15, y = 15, w = 5, h = 5, count = 20, time = 7200},
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
