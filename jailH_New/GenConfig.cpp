/*
 * Module to generate config.c files from GUI
 *
 *  Author :
 *
 *  Copyright (C) 2017 , All Rights Reserved.
 */

#include "GenConfig.h"
#include <numeric>
#include <stdio.h>
#include <string>
#include <sstream>
#include "config_string.h"
#include "RootCell.h"
#include "util.h"

GenConfig::GenConfig(JailHouseCell & j)
{
    std::string file_name( j.get_name() + ".c" );
    pf = fopen(file_name.c_str(),"w");
    writeFile(j);
}


std::string GenConfig::getHexStr(UNS_64 n)const
{
    std::stringstream s;
    s << std::hex << n;
    std::string str("0x"+s.str());
    return str;
}

// To write into the file
void GenConfig::writeFile(JailHouseCell & j)
{
    if(RootCell *r = dynamic_cast<RootCell *>(&j))
    {
        using namespace root;
        fprintf(pf,header);
        fprintf(pf,struct_heading,
                //   std::to_string(j.get_cpu_count()).c_str(),
                std::to_string(j.get_mem_Regioncount()).c_str(),
                std::to_string(j.get_irqcount()).c_str(),
                std::to_string(j.get_pcicount()).c_str() );
        {
            auto hpm = r->get_Hypervisor_Memory();
            fprintf(pf,root_header,
                    (j.get_signature()).c_str(),
                    (j.get_revision()).c_str(),
                    getHexStr(hpm.phys_start).c_str(),
                    getHexStr(hpm.size).c_str() );
        }
        {
            auto dc = r->get_Debug_Console();
            fprintf(pf,root_debug_console,
                    getHexStr(dc.address).c_str(),
                    getHexStr(dc.size).c_str(),
                    string_from_vector((r->get_Debug_Console()).flags).c_str()
                    //(dc.flags).c_str()
                    );
        }
        {
            auto pi = r->get_Platform_Info();
            fprintf(pf,root_paltform_info,
                    getHexStr(pi.pci_mmconfig_base).c_str(),
                    std::to_string(pi.pci_mmconfig_end_bus).c_str(),
                    std::to_string(pi.pci_is_virtual).c_str(),
                    //std::to_string(pi.gic_version).c_str(),
                    getHexStr(pi.gicd_base).c_str(),
                    getHexStr(pi.gicc_base).c_str(),
                    getHexStr(pi.gich_base).c_str(),
                    getHexStr(pi.gicv_base).c_str(),
                    std::to_string(pi.maintenance_irq).c_str());

        }
        fprintf(pf,root_cell,
                (j.get_name()).c_str(),
                std::to_string(j.get_vpci_irq_base()).c_str(),
                vec_to_hex(j.get_cpuIds()).c_str() );
    }
    else
    {
        using namespace non_root;
        fprintf(pf,header);
        fprintf(pf,struct_heading,
                //     std::to_string(j.get_cpu_count()).c_str(),
                std::to_string(j.get_mem_Regioncount()).c_str(),
                std::to_string(j.get_irqcount()).c_str(),
                std::to_string(j.get_pcicount()).c_str() );
        fprintf(pf,cell_body,
                (j.get_signature()).c_str(),
                (j.get_revision()).c_str(),
                (j.get_name()).c_str(),
                string_from_vector(j.get_flags()).c_str(),
                std::to_string(j.get_vpci_irq_base()).c_str(),
                vec_to_hex(j.get_cpuIds()).c_str() );
    }
    fprintf(pf,mem_start);
    auto mem_itr = j.get_memRegionItr_begin();
    for(;mem_itr != j.get_memRegionItr_end();++mem_itr)
    {
        write_mem_region(mem_itr->second);
    }
    fprintf(pf,mem_end);

    fprintf(pf,irq_start);
    auto irq_itr = j.get_irqChipItr_begin();
    for(;irq_itr != j.get_irqChipItr_end(); ++ irq_itr)
    {
        write_irq_chip(irq_itr->second);
    }
    fprintf(pf,irq_end);

    fprintf(pf,pci_start);
    auto pci_itr = j.get_pciDeviceItr_begin();
    for(;pci_itr != j.get_pciDeviceItr_end(); ++pci_itr)
    {
        write_pci_device(pci_itr->second);
    }
    fprintf(pf,pci_end);

    fprintf(pf,file_end);

}

// To write mem_region sructure elements into config.c file
void GenConfig::write_mem_region(MemRegion & m)
{

    fprintf(pf, mem_body,
            m.get_name().c_str(),
            getHexStr(m.get_phys_start()).c_str(),
            getHexStr(m.get_virt_start()).c_str(),
            getHexStr(m.get_size()).c_str(),
            string_from_vector(m.get_flags()).c_str() ) ;
}

// To write pci_device sructure elements into config.c file
void GenConfig::write_pci_device(PciDevice & pci)
{
    auto bar_vec = pci.get_bar_mask();
    auto bar_str = hexVecToString(bar_vec);
    fprintf(pf,pci_body,
            pci.get_type().c_str(),
            getHexStr(pci.get_bdf()).c_str(),
            bar_str.c_str(),
            std::to_string(pci.get_shmem_region()).c_str(),
            (pci.get_shmem_protocol()).c_str());
}


// To write irq-chips sructure elements into config.c file
void GenConfig::write_irq_chip(IrqChip &  irq)
{
    auto bm_vector = irq.get_pin_bitmap();
    auto bm_str = hexVecToString(bm_vector);
    fprintf(pf, irq_body,
            irq.get_name().c_str(),
            getHexStr( irq.get_address()).c_str(),
            std::to_string(irq.get_pin_base()).c_str(),
            bm_str.c_str());
}


// function to convert vector to hex
std::string GenConfig::hexVecToString( std::vector<UNS_64> & vec) const
{
    std::string ret_str="";
    if( vec.size() ==0 )
        return ret_str;
    for( auto & val : vec)
    {
        std::stringstream s;
        s << std::hex << val;
        std::string str("0x"+s.str());
        ret_str = ret_str + str + ",";
    }
    return std::string(std::begin(ret_str),std::end(ret_str) -1 );
}


// function to convert vector to hex
std::string  GenConfig::vec_to_hex(std::vector<bool> vec) const
{

    UNS_64 temp = 0;
    int n = 0 ;
    //std::reverse(vec.begin(),vec.end());
    for (const auto & i : vec) {
        if (i)
            temp |= 1 << n ;
        n++ ;
    }
    return getHexStr(temp);
}




GenConfig::~GenConfig()
{
    fclose(pf);
}





