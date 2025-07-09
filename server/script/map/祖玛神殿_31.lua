local addmon = require('map.addmonster')
local addMonCo = addmon.monGener( -- 祖玛神殿_31
{
    {
        name = '千年毒蛇',
        loc = {
            {x = 150, y = 150, w = 150, h = 150, count = 8, time = 1200},
        }
    },
    {
        name = '半兽人',
        loc = {
            {x = 150, y = 150, w = 150, h = 150, count = 8, time = 600},
        }
    },
    {
        name = '多角虫',
        loc = {
            {x = 150, y = 150, w = 150, h = 150, count = 8, time = 600},
        }
    },
    {
        name = '多角虫0',
        loc = {
            {x = 150, y = 150, w = 150, h = 150, count = 1, time = 9000},
        }
    },
    {
        name = '威思尔小虫',
        loc = {
            {x = 150, y = 150, w = 150, h = 150, count = 8, time = 600},
        }
    },
    {
        name = '森林雪人',
        loc = {
            {x = 150, y = 150, w = 150, h = 150, count = 8, time = 600},
        }
    },
    {
        name = '森林雪人0',
        loc = {
            {x = 150, y = 150, w = 150, h = 150, count = 1, time = 9000},
        }
    },
    {
        name = '沙漠威思尔小虫',
        loc = {
            {x = 150, y = 150, w = 150, h = 150, count = 8, time = 600},
        }
    },
    {
        name = '狼',
        loc = {
            {x = 150, y = 150, w = 150, h = 150, count = 8, time = 600},
        }
    },
    {
        name = '猎鹰',
        loc = {
            {x = 150, y = 150, w = 150, h = 150, count = 8, time = 600},
        }
    },
    {
        name = '猎鹰0',
        loc = {
            {x = 150, y = 150, w = 150, h = 150, count = 1, time = 9000},
        }
    },
    {
        name = '盔甲虫',
        loc = {
            {x = 150, y = 150, w = 150, h = 150, count = 8, time = 600},
            {x = 150, y = 150, w = 150, h = 150, count = 8, time = 600},
        }
    },
    {
        name = '盔甲虫0',
        loc = {
            {x = 150, y = 150, w = 150, h = 150, count = 1, time = 9000},
        }
    },
    {
        name = '红蛇',
        loc = {
            {x = 150, y = 150, w = 150, h = 150, count = 8, time = 600},
        }
    },
    {
        name = '虎蛇',
        loc = {
            {x = 150, y = 150, w = 150, h = 150, count = 8, time = 600},
        }
    },
    {
        name = '虎蛇0',
        loc = {
            {x = 150, y = 150, w = 150, h = 150, count = 1, time = 9000},
        }
    },
    {
        name = '食人花',
        loc = {
            {x = 150, y = 150, w = 150, h = 150, count = 8, time = 600},
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
