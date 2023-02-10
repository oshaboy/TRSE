#include "system6809.h"

#include "source/LeLib/util/util.h"
#include "source/LeLib/util/cinifile.h"

//#include "source/LeLib/util/lz4/lz4.h"

System6809::System6809(QSharedPointer<CIniFile> settings, QSharedPointer<CIniFile> proj) : AbstractSystem(settings, proj) {
    m_allowedGlobalTypeFlags << "compressed" <<"pure"<<"pure_variable" <<"pure_number" << "signed" <<"no_term";
    m_allowedProcedureTypeFlags << "pure"<<"pure_variable" <<"pure_number" << "signed" <<"no_term" <<"global";
    m_exomizerName ="Compress executable";
    m_renameVariables << "a" <<"b"<<"x"<<"y";

    //        m_registers <<"_a" <<"_b"<<"_c"<<"_d"<<"_af"<<"_bc"<<"_de"<<"_hl"<<"_ix"<<"_iy"<<"_h"<<"_l";
}

void System6809::Assemble(QString &text, QString filename, QString currentDir, QSharedPointer<SymbolTable> symTab)
{
    QString output;
    //    AssembleZOrgasm(output,text,filename,currentDir,symTab);

}

void System6809::PostProcess(QString &text, QString file, QString currentDir)
{
}


void System6809::PerformAssembling(QString filename, QString &text,QString currentDir, QSharedPointer<SymbolTable> symTab)
{
    bool useOrgasm = false;
    //    if (m_settingsIni->contains("assembler_TRS80CoCo"))
    //          useOrgasm = m_settingsIni->getString("assembler_TRS80CoCo")!="Pasmo";


    QString assembler = m_settingsIni->getString("lwasm");
    bool useMorgasm = (m_settingsIni->getString("assembler_6809")=="orgasm");
    if (QFile::exists(filename+".bin"))
        QFile::remove(filename+".bin");

    QString output = "";
    QString format = "-r";
    if (m_system==TRS80COCO)
        format ="-decb";
//    StartProcess(assembler, QStringList() << "-9bl" <<"-p" <<"cd"<<filename+".asm" <<"-o"+filename+".bin", text);
    if (useMorgasm) {
        AssembleZOrgasm(output,text,filename,currentDir, symTab,1);
    }
    else
        StartProcess(assembler, QStringList() << format<<"--6809"  <<filename+".asm" <<"-o"+filename+".bin" << "--symbol-dump="+filename+".sym", text);


}

QString System6809::CompressFile(QString fileName)
{
    return CompressZX0(fileName);
}
