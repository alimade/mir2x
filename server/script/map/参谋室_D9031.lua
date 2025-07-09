local addmon = require('map.addmonster')
local addMonCo = addmon.monGener( -- 参谋室_D9031
{
    {
        name = '爆毒神魔',
        loc = {
            {x = 10, y = 10, w = 5, h = 5, count = 1, time = 1200},
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
