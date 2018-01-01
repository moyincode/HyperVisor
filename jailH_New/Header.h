#ifndef HEADER_H
#define HEADER_H


std::map<std::string , std::string> Mem_Flags = { {"RD","JAILHOUSE_MEM_READ"},
                                                  {"WR","JAILHOUSE_MEM_WRITE"},
                                                  {"IO","JAILHOUSE_MEM_IO"},
                                                  {"EX","JAILHOUSE_MEM_EXECUTE"}
                                                };


std::vector<std::string> Debug_Console_Flags = { "JAILHOUSE_CON1_TYPE_8250",
                                                 "JAILHOUSE_CON1_ACCESS_MMIO",
                                                 "JAILHOUSE_CON1_REGDIST_4",
                                                 "JAILHOUSE_CON2_TYPE_ROOTPAGE"
                                               } ;


std::vector<std::string> Cell_Desc_Flags = { "JAILHOUSE_CELL_PASSIVE_COMMREG", "JAILHOUSE_CELL_DEBUG_CONSOLE" } ;

std::map<std::string, int> CPU_id =  { {"TX1",4},{"TX2",6}, {"TX3",12}} ;




#endif // HEADER_H
