
local tp = require('npc.include.teleport')
setEventHandler(
{
    [SYS_ENTER] = function(uid, value)
        tp.uidReqSpaceMove(uid, '潘夜神殿3层西部_D11031', 200, 256)
    end,
})
