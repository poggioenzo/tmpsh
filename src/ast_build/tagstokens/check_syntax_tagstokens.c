
#include "tagstokens.h"
// #include "tagstokensmonitor.h"
// #include "shiftreduce.h"


// def check_syntax(self):
//     import utils.tagstokensmonitor as ttm
//     ttm.TagsTokensMonitor(self)
//     if self.valid:
//         self.stack = sr.tagstokens_shift_reduce(self, gv.GRAMMAR)
//         if self.length > 0 and end_escape(self.tokens[-1]):
//             self.incomplete = True
//     if gv.HEREDOCS != [] and self.not_heredoc:
//         self.incomplete |= not all([elt.closed and
//                                     not elt.tagstokens.incomplete
//                                     for elt in gv.HEREDOCS])
//         self.valid &= all([elt.tagstokens.valid for elt in gv.HEREDOCS])
//     self.clear_stack()
//     return self
//



void check_syntax_tagstokens(t_tagstokens *self)
{
    // init_tagstokensmonitor(self);
    if (self->valid)
    {
        // self->stack = tgtk_shiftreduce(self, g_grammar->grammar);
        if (self->length > 0 && )

    }
    clear_stack_tagstokens(self);
}
