local addmon = require('map.addmonster')
local addMonCo = addmon.monGener( -- 神圣战甲术空间_D420_001
{
    {
        name = '尸王61',
        loc = {
            {x = 25, y = 25, w = 25, h = 25, count = 10, time = 60},
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
