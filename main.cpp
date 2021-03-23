#include <iostream>
#include "Parser.h"

int main() {
    std::string grammar = "A: a SH1 | a SH2 | a SH3 | a SH4 | a SH5 $ SH1: sh1 SV1 | sh1 SV2 | sh1 SV3 $ SH2: sh2 SV1 | sh2 SV2 $ "
                          "SH3:  sh3 SV1  | sh3 SV2  | sh3 SV3 $ SH4: sh4 SV3 | sh4 SV4 | sh4 SV5 $ SH5: sh5 SV3 | sh5 SV5 $ "
                          "SV1: sv1 N1 | sv1 N2 | sv1 N3 $ SV2: sv2 N1 | sv2 N2 | sv2 N3 $ SV3: sv3 N4 | sv3 N5 $ "
                          "SV4: sv4 N4 | sv4 N5 $ SV5: sv5 N5  $ N1: n1 AC1 | n1 AC2 $ N2: n2 AC1 | n2 AC2 | n2 AC3 $ "
                          "N3: n3 AC2 | n3 AC3 | n3 AC4 $ N4: n4 AC2 | n4 AC3 | n4 AC4 $ N5: n5 AC4 $ AC1: ac1 C1 | ac1 C2 | ac1 C3 $ "
                          "AC2: ac2 C1 | ac2 C2 | ac2 C3 $ AC3: ac3 C1 | ac3 C2 | ac3 C3 $ AC4: ac4 C4\ $ C1: c1 C2 $ "
                          "C2: c2 C4 $ C3: c3 a $ C4: c4 a";
    std::string terminals = "a sh1 sh2 sh3 sh4 sh5 sv1 sv2 sv3 sv4 sv5 n1 n2 n3 n4 n5 ac1 ac2 ac3 ac4 c1 c2 c3 c4";
    std::string non_terminals = "A SH1 SH2 SH3 SH4 SH5 SV1 SV2 SV3 SV4 SV5 N1 N2 N3 N4 N5 AC1 AC2 AC3 AC4 C1 C2 C3 C4";
    Parser parser(grammar, terminals, non_terminals, "A");
    parser.lexeme("A Sh1 Sv1 Ac1 N1 C1 C2 C4 A");

    return 0;
}
