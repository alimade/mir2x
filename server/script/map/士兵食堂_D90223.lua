local addmon = require('map.addmonster')
local addMonCo = addmon.monGener( -- 士兵食堂_D90223
{
    {
        name = '犬猴魔',
        loc = {
            {x = 13, y = 13, w = 13, h = 13, count = 1, time = 1200},
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
