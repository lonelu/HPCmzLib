﻿/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 * Copyright (c) 2019-2020 University of Houston. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 */
#include "MzmlMethods.h"
#include "../MassSpectrometry/MsDataFile.h"
#include "../MassSpectrometry/MzSpectra/MzSpectrum.h"
#include "../MzLibUtil/MzRange.h"
#include "XSD/mzML1.1.0.h"
#include "XSD/mzML1.1.1_idx.h"
#include <experimental/filesystem>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <../include/stringhelper.h>
#include <cmath>
using namespace MassSpectrometry;
using namespace MzLibUtil;

namespace IO
{
    namespace MzML
    {
std::unordered_map<DissociationType, std::string> MzmlMethods::DissociationTypeAccessions =
{
    {DissociationType::CID, "MS:1000133"},
    {DissociationType::ISCID, "MS:1001880"},
    {DissociationType::HCD, "MS:1000422"},
    {DissociationType::ETD, "MS:1000598"},
    {DissociationType::IRMPD, "MS:1000435"},
    {DissociationType::PQD, "MS:1000599"},
    {DissociationType::Unknown, "MS:1000044"}
};
std::unordered_map<DissociationType, std::string> MzmlMethods::DissociationTypeNames =
{
    {DissociationType::CID, "collision-induced dissociation"},
    {DissociationType::ISCID, "in-source collision-induced dissociation"},
    {DissociationType::HCD, "beam-type collision-induced dissociation"},
    {DissociationType::ETD, "electron transfer dissociation"},
    {DissociationType::IRMPD, "photodissociation"},
    {DissociationType::PQD, "pulsed q dissociation"},
    {DissociationType::Unknown, "dissociation method"}
};
std::unordered_map<MZAnalyzerType, std::string> MzmlMethods::analyzerDictionary =
{
    {MZAnalyzerType::Unknown, "MS:1000443"},
    {MZAnalyzerType::Quadrupole, "MS:1000081"},
    {MZAnalyzerType::IonTrap2D, "MS:1000291"},
    {MZAnalyzerType::IonTrap3D,"MS:1000082"},
    {MZAnalyzerType::Orbitrap,"MS:1000484"},
    {MZAnalyzerType::TOF,"MS:1000084"},
    {MZAnalyzerType::FTICR,"MS:1000079"},
    {MZAnalyzerType::Sector,"MS:1000080"}
};
std::unordered_map<std::string, std::string> MzmlMethods::nativeIdFormatAccessions =
{
    {"scan number only nativeID format", "MS:1000776"},
    {"Thermo nativeID format", "MS:1000768"},
    {"no nativeID format", "MS:1000824"}
};
std::unordered_map<std::string, std::string> MzmlMethods::MassSpectrometerFileFormatAccessions =
{
    {"Thermo RAW format", "MS:1000563"},
    {"mzML format", "MS:1000584"}
};
std::unordered_map<std::string, std::string> MzmlMethods::FileChecksumAccessions =
{
    {"MD5", "MS:1000568"},
    {"SHA-1", "MS:1000569"}
};
std::unordered_map<bool, std::string> MzmlMethods::CentroidAccessions =
{
    {true, "MS:1000127"},
    {false, "MS:1000128"}
};
std::unordered_map<bool, std::string> MzmlMethods::CentroidNames =
{
    {true, "centroid spectrum"},
    {false, "profile spectrum"}
};
std::unordered_map<Polarity, std::string> MzmlMethods::PolarityAccessions =
{
    {Polarity::Negative, "MS:1000129"},
    {Polarity::Positive, "MS:1000130"}
};
std::unordered_map<Polarity, std::string> MzmlMethods::PolarityNames =
{
    {Polarity::Negative, "negative scan"},
    {Polarity::Positive, "positive scan"}
};

        void MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(MsDataFile *myMsDataFile, const std::string &outputFile, bool writeIndexed)
        {
            //returns filename WITH extension
            std::string title_with_extension = std::experimental::filesystem::path(outputFile).filename();

            //remove file extension from name
            size_t lastindex = title_with_extension.find_last_of("."); 
            std::string title = title_with_extension.substr(0, lastindex); 

            std::string idTitle = isdigit(title[0]) ? "id:" + title : title;

            //creating CVList of size 2 for mzML
            ms::mzml::CVListType *tempVar = new ms::mzml::CVListType(2);

            //Creating 2 CVTypes for CVlist for mzML
            ms::mzml::CVType *tempVar3 = new ms::mzml::CVType("MS", "Proteomics Standards Initiative Mass Spectrometry Ontology", "https://raw.githubusercontent.com/HUPO-PSI/psi-ms-CV/master/psi-ms.obo");
            tempVar3->version("4.0.1");

            ms::mzml::CVType *tempVar4 = new ms::mzml::CVType("UO", "Unit Ontology", "http://obo.cvs.sourceforge.net/*checkout*/obo/obo/ontology/phenotype/unit.obo");
            tempVar4->version("12:10:2011");

            //add cvtypes to cvlist
            tempVar->cv().push_back(*tempVar3);
            tempVar->cv().push_back(*tempVar4);

            ms::mzml::ParamGroupType tempVar6 = ms::mzml::ParamGroupType();
            ms::mzml::FileDescriptionType tempVar5 = ms::mzml::FileDescriptionType(tempVar6);

            ms::mzml::SourceFileListType tempVar8 = ms::mzml::SourceFileListType(1);

            //removed 13 repetitive calls
            auto source_file = myMsDataFile->getSourceFile();

            if (source_file->getNativeIdFormat() != "" && source_file->getMassSpectrometerFileFormat() != "" && source_file->getFileChecksumType() != "")
            {
                std::string idName = isdigit(source_file->getFileName()[0]) ? "id:" + source_file->getFileName()[0] : source_file->getFileName();

                ms::mzml::SourceFileType *tempVar9 = new ms::mzml::SourceFileType(idName, source_file->getFileName(), source_file->getUri()->getFileName());
                tempVar8.sourceFile().push_back(*tempVar9);


                ms::mzml::CVParamType *tempVar10 = new ms::mzml::CVParamType("MS", nativeIdFormatAccessions[source_file->getNativeIdFormat()], source_file->getNativeIdFormat());
                tempVar10->value("");

                //removed 4 repetitive function calls
                auto cv_param = &tempVar8.sourceFile()[0].cvParam();
                cv_param->push_back(*tempVar10);

                ms::mzml::CVParamType *tempVar11 = new ms::mzml::CVParamType("MS", MassSpectrometerFileFormatAccessions[source_file->getMassSpectrometerFileFormat()], source_file->getMassSpectrometerFileFormat());
                tempVar11->value("");
                cv_param->push_back(*tempVar11);

                ms::mzml::CVParamType *tempVar12 = new ms::mzml::CVParamType("MS", FileChecksumAccessions[source_file->getFileChecksumType()], source_file->getFileChecksumType());

                std::string tempVar13 = source_file->getCheckSum();
                
                tempVar12->value((!tempVar13.empty()) ? tempVar13 : "");
                cv_param->push_back(*tempVar12);
            }
	      
            ms::mzml::CVParamType *tempVar14 = new ms::mzml::CVParamType("MS", "MS:1000579", "MS1 spectrum");
            tempVar14->value("");

            tempVar5.fileContent().cvParam().push_back(*tempVar14);

            ms::mzml::CVParamType *tempVar15 = new ms::mzml::CVParamType("MS", "MS:1000580", "MSn spectrum");
            tempVar15->value("");
            tempVar5.fileContent().cvParam().push_back(*tempVar15);

            ms::mzml::SoftwareListType *tempVar16 = new ms::mzml::SoftwareListType(2);

            // TODO: add the raw file fields
            ms::mzml::SoftwareType *tempVar17 = new ms::mzml::SoftwareType("mzLib", "1");
            tempVar16->software().push_back(*tempVar17);

            ms::mzml::CVParamType *tempVar18 = new ms::mzml::CVParamType("MS", "MS:1000799", "custom unreleased software tool");
            tempVar18->value("mzLib");
            tempVar16->software()[0].cvParam().push_back(*tempVar18);

            std::vector<MassSpectrometry::MsDataScan*> dataScans = myMsDataFile->GetAllScansList();
            std::vector<MZAnalyzerType> analyzersInThisFile;
            for (auto i : dataScans){
                analyzersInThisFile.push_back(i->getMzAnalyzer());
            }

            std::unordered_map<MZAnalyzerType, std::string> analyzersInThisFileDict;
            // Leaving empty. Can't figure out the configurations.
            // ToDo: read instrumentConfigurationList from mzML file
            ms::mzml::InstrumentConfigurationListType *tempVar19 = new ms::mzml::InstrumentConfigurationListType(analyzersInThisFile.size());

            // Write the analyzers, also the default, also in the scans if needed
            for (long long unsigned int i = 0; i < tempVar19->count(); i++)
            {

                analyzersInThisFileDict[analyzersInThisFile[i]] = "IC" + std::to_string(i + 1);
                ms::mzml::InstrumentConfigurationType *tempVar20 = new ms::mzml::InstrumentConfigurationType("IC" + std::to_string(i + 1));

                ms::mzml::ComponentListType *tempVar21 = new ms::mzml::ComponentListType(3);

                ms::mzml::CVParamType *tempVar22 = new ms::mzml::CVParamType("MS", "MS:1000031", "instrument model");
                tempVar22->value("");
                tempVar20->cvParam().push_back(*tempVar22);

                ms::mzml::SourceComponentType *tempVar23 = new ms::mzml::SourceComponentType(1);

                ms::mzml::CVParamType *tempVar24 = new ms::mzml::CVParamType("MS", "MS:1000008", "ionization type");
                tempVar24->value("");
                tempVar23->cvParam().push_back(*tempVar24);

                ms::mzml::AnalyzerComponentType *tempVar25 = new ms::mzml::AnalyzerComponentType(2);
                std::string anName = "";

                //Nick TODO Add toString method to MzAnalyzerType
                //MzAnalyzerType is enum class with the following values:
                // Unknown = 0,
                // Quadrupole = 1,
                // IonTrap2D = 2,
                // IonTrap3D = 3,
                // Orbitrap = 4,
                // TOF = 5,
                // FTICR = 6,
                // Sector = 7

                if (analyzersInThisFile[i] == MZAnalyzerType::Unknown)
                {
                    anName = "mass analyzer type";
                }
                else
                {
                    if (analyzersInThisFile[i] == MZAnalyzerType::Quadrupole)
                        anName = "Quadrupole";
                    else if (analyzersInThisFile[i] == MZAnalyzerType::IonTrap2D)
                        anName = "IonTrap2D";
                    else if (analyzersInThisFile[i] == MZAnalyzerType::IonTrap3D)
                        anName = "IonTrap3D";
                    else if (analyzersInThisFile[i] == MZAnalyzerType::Orbitrap)
                        anName = "Orbitrap";
                    else if (analyzersInThisFile[i] == MZAnalyzerType::TOF)
                        anName = "TOF";
                    else if (analyzersInThisFile[i] == MZAnalyzerType::FTICR)
                        anName = "FTICR";
                    else if (analyzersInThisFile[i] == MZAnalyzerType::Sector)
                        anName = "Sector";
                }

                ms::mzml::CVParamType *tempVar26 = new ms::mzml::CVParamType("MS", analyzerDictionary[analyzersInThisFile[i]], anName);
                tempVar26->value("");
                tempVar25->cvParam().push_back(*tempVar26);

                ms::mzml::DetectorComponentType *tempVar27 = new ms::mzml::DetectorComponentType(3);
                ms::mzml::CVParamType *tempVar28 = new ms::mzml::CVParamType("MS", "MS:1000026", "detector type");
                tempVar28->value("");
                tempVar27->cvParam().push_back(*tempVar28);

                //add sourcecomponenttype (tempVar23), analyzer component type (tempVar25), and detector component type (tempVar27) to component list type (tempVar21)
                tempVar21->source().push_back(*tempVar23);
                tempVar21->analyzer().push_back(*tempVar25);
                tempVar21->detector().push_back(*tempVar27);

                tempVar20->componentList(*tempVar21);

                //add instrumentConfiguration (tempVar20) to instrumentonfigurationList (tmepVar19)
                tempVar19->instrumentConfiguration().push_back(*tempVar20);

                delete tempVar28;
                delete tempVar27;
                delete tempVar26;
                delete tempVar25;
                delete tempVar24;
                delete tempVar23;
                delete tempVar22;
                delete tempVar20;
            }

            ms::mzml::DataProcessingListType *tempVar29 = new ms::mzml::DataProcessingListType(1);

            // Only writing mine! Might have had some other data processing (but not if it is a raw file)
            // ToDo: read dataProcessingList from mzML file
            ms::mzml::DataProcessingType *tempVar30 = new ms::mzml::DataProcessingType("mzLibProcessing");
            tempVar29->dataProcessing().push_back(*tempVar30);

            ms::mzml::ProcessingMethodType *tempVar31 = new ms::mzml::ProcessingMethodType(0, "mzLib");

            ms::mzml::CVParamType *tempVar32 = new ms::mzml::CVParamType("MS", "MS:1000544", "Conversion to mzML");
            tempVar32->value("");

            //add cvparam to processingmethodtype (tempVar31)
            tempVar31->cvParam().push_back(*tempVar32);

            tempVar29->dataProcessing()[0].processingMethod().push_back(*tempVar31);

            ms::mzml::RunType *tempVar33 = new ms::mzml::RunType(idTitle, analyzersInThisFileDict[analyzersInThisFile[0]]);

            ms::mzml::mzMLType *mzML_type = new ms::mzml::mzMLType(*tempVar, tempVar5, *tempVar16, *tempVar19, *tempVar29, *tempVar33, "1.1.0");

            ms::mzml::ChromatogramListType *tempVar34 = new ms::mzml::ChromatogramListType(1, "mzLibProcessing");
            mzML_type->run().chromatogramList(*tempVar34);

            //Chromatagram info
            ms::mzml::BinaryDataArrayListType *tempVar36 = new ms::mzml::BinaryDataArrayListType(2);

            ms::mzml::ChromatogramType *tempVar35 = new ms::mzml::ChromatogramType(*tempVar36, "TIC", 0, myMsDataFile->getNumSpectra());
            tempVar35->dataProcessingRef("mzLibProcessing");

            mzML_type->run().chromatogramList()->chromatogram().push_back(*tempVar35);

            ms::mzml::CVParamType *tempVar37 = new ms::mzml::CVParamType("MS", "MS:1000235", "total ion current chromatogram");
            tempVar37->value("");
            mzML_type->run().chromatogramList()->chromatogram()[0].cvParam().push_back(*tempVar37);

            std::vector<double> times(myMsDataFile->getNumSpectra());
            std::vector<double> intensities(myMsDataFile->getNumSpectra());

            for (int i = 1; i <= myMsDataFile->getNumSpectra(); i++)
            {
                times[i - 1] = myMsDataFile->GetOneBasedScan(i)->getRetentionTime();
                intensities[i - 1] = myMsDataFile->GetOneBasedScan(i)->getMassSpectrum()->getSumOfAllY();
            }

            std::vector<unsigned char> bin_times_vector = MzSpectrum::Get64Bitarray(times);
            unsigned char bin_times[bin_times_vector.size()]; 
            std::copy(bin_times_vector.begin(), bin_times_vector.end(), bin_times);
            xml_schema::base64_binary bindata((void*)bin_times, (sizeof(bin_times)/sizeof(*bin_times))); 
	    
            ms::mzml::BinaryDataArrayType *tempVar38 = new ms::mzml::BinaryDataArrayType(bindata, (size_t)(4 * (double)ceil((static_cast<double>(bindata.encode().length()) / 3))));
            mzML_type->run().chromatogramList()->chromatogram()[0].binaryDataArrayList().binaryDataArray().push_back(*tempVar38);

            ms::mzml::CVParamType *tempVar39 = new ms::mzml::CVParamType("MS","MS:1000523","64-bit float");
            tempVar39->value("");

            //removed 10 repetitive function calls
            auto binary_data_array = &mzML_type->run().chromatogramList()->chromatogram()[0].binaryDataArrayList().binaryDataArray()[0];            
            binary_data_array->cvParam().push_back(*tempVar39);

            ms::mzml::CVParamType *tempVar40 = new ms::mzml::CVParamType("MS", "MS:1000576", "no compression");
            tempVar40->value("");
            binary_data_array->cvParam().push_back(*tempVar40);

            ms::mzml::CVParamType *tempVar41 = new ms::mzml::CVParamType("MS", "MS:1000595", "time array");
            tempVar41->unitCvRef("UO");
            tempVar41->unitAccession("UO:0000031");
            tempVar41->unitName("Minutes");
            tempVar41->value("");
            binary_data_array->cvParam().push_back(*tempVar40);

            //Chromatogram Y axis (total intensity)
            std::vector<unsigned char> bin_intensities_vector = MzSpectrum::Get64Bitarray(intensities);
            unsigned char bin_intensities[bin_intensities_vector.size()]; 
            std::copy(bin_intensities_vector.begin(), bin_intensities_vector.end(), bin_intensities);
            xml_schema::base64_binary bindata_intensities((void*)bin_intensities, (sizeof(bin_intensities)/sizeof(*bin_intensities))); 

            ms::mzml::BinaryDataArrayType *tempVar42 = new ms::mzml::BinaryDataArrayType(bindata_intensities, (size_t)(4 * (double)ceil((static_cast<double>(bindata_intensities.encode().length()) / 3))));

            mzML_type->run().chromatogramList()->chromatogram()[0].binaryDataArrayList().binaryDataArray().push_back(*tempVar42);

            ms::mzml::CVParamType *tempVar43 = new ms::mzml::CVParamType("MS", "MS:1000523", "64-bit float");
            tempVar43->value("");

            //removed 10 repetitive function calls
            binary_data_array = &mzML_type->run().chromatogramList()->chromatogram()[0].binaryDataArrayList().binaryDataArray()[1];
            binary_data_array->cvParam().push_back(*tempVar43);

            ms::mzml::CVParamType *tempVar44 = new ms::mzml::CVParamType("MS", "MS:1000576", "no compression");
            tempVar44->value("");
            binary_data_array->cvParam().push_back(*tempVar44);

            ms::mzml::CVParamType *tempVar45 = new ms::mzml::CVParamType("MS", "MS:1000515", "intensity array");
            tempVar45->unitAccession("MS:1000131");
            tempVar45->unitName("number of counts");
            tempVar45->unitCvRef("MS");
            tempVar45->value("");
            binary_data_array->cvParam().push_back(*tempVar45);

            ms::mzml::SpectrumListType *tempVar46 = new ms::mzml::SpectrumListType((myMsDataFile->getNumSpectra()), "mzLibProcessing");
            mzML_type->run().spectrumList(*tempVar46);

            // Loop over all spectra
            for (int i = 1; i <= myMsDataFile->getNumSpectra(); i++)
            {
                ms::mzml::SpectrumType *tempVar47 = new ms::mzml::SpectrumType(myMsDataFile->GetOneBasedScan(i)->getNativeId(), i - 1, myMsDataFile->GetOneBasedScan(i)->getMassSpectrum()->getYArray().size());
                tempVar47->id(myMsDataFile->GetOneBasedScan(i)->getNativeId());

                //push back 9 cvparams for tempVar47
                ms::mzml::ScanListType *tempVar48 = new ms::mzml::ScanListType(0);
                tempVar47->scanList(*tempVar48);

                //need 9 cvparams
                mzML_type->run().spectrumList().get().spectrum().push_back(*tempVar47);

                ms::mzml::ScanListType *tempScanList = new ms::mzml::ScanListType(1);

                mzML_type->run().spectrumList().get().spectrum()[i - 1].scanList(*tempScanList);

                if (myMsDataFile->GetOneBasedScan(i)->getMsnOrder() == 1)
                {
                    ms::mzml::CVParamType *tempVar49 = new ms::mzml::CVParamType("MS", "MS:1000579", "MS1 spectrum");
                    tempVar49->value("");
                    mzML_type->run().spectrumList().get().spectrum()[i - 1].cvParam().push_back(*tempVar49);

                    delete tempVar49;
                }
                else if (myMsDataFile->GetOneBasedScan(i)->getMsnOrder() != 1)
                {
                    auto scanWithPrecursor = myMsDataFile->GetOneBasedScan(i);
                    ms::mzml::CVParamType *tempVar50 = new ms::mzml::CVParamType("MS", "MS:1000580", "MSn spectrum");
                    tempVar50->value("");

                    mzML_type->run().spectrumList().get().spectrum()[i - 1].cvParam().push_back(*tempVar50);

                    // So needs a precursor!
                    ms::mzml::PrecursorListType *tempPrecursor = new ms::mzml::PrecursorListType(1);
                    mzML_type->run().spectrumList().get().spectrum()[i - 1].precursorList(*tempPrecursor);

                    //PrecursorType needs activationType in constructor.  This is defined on lines 893 - 904.  those lines have been modified and moved here
                    ms::mzml::ParamGroupType *tempActivation = new ms::mzml::ParamGroupType();
                    DissociationType dissociationType = scanWithPrecursor->getDissociationType().value();
                    ms::mzml::CVParamType *activationCVParam = new ms::mzml::CVParamType("MS", DissociationTypeAccessions[dissociationType], DissociationTypeNames[dissociationType]);
                    activationCVParam->value("");

                    ms::mzml::PrecursorType *tempVar51 = new ms::mzml::PrecursorType(*tempActivation);
                    ms::mzml::SelectedIonListType *tempVar52 = new ms::mzml::SelectedIonListType(1);
                    tempVar51->selectedIonList(*tempVar52);

                    ms::mzml::ParamGroupType *selectedIonParam = new ms::mzml::ParamGroupType();
                    tempVar51->selectedIonList()->selectedIon().push_back(*selectedIonParam);

                    mzML_type->run().spectrumList().get().spectrum()[i - 1].precursorList()->precursor().push_back(*tempVar51);
                    mzML_type->run().spectrumList().get().spectrum()[i - 1].precursorList()->precursor()[0].activation().cvParam().push_back(*activationCVParam);

                    if (scanWithPrecursor->getOneBasedPrecursorScanNumber())
                    {
                        std::string precursorID = myMsDataFile->GetOneBasedScan(scanWithPrecursor->getOneBasedPrecursorScanNumber().value())->getNativeId();
                        mzML_type->run().spectrumList().get().spectrum()[i - 1].precursorList()->precursor()[0].spectrumRef() = precursorID;
                    }

                    ms::mzml::ParamGroupType *tempVar53 = new ms::mzml::ParamGroupType();

                    //pushback 3 cvparams
                    mzML_type->run().spectrumList().get().spectrum()[i - 1].precursorList()->precursor()[0].selectedIonList()->selectedIon()[0] = *tempVar53;

                    // Selected ion MZ
                    ms::mzml::CVParamType *tempVar54 = new ms::mzml::CVParamType("MS", "MS:1000744", "selected ion m/z");

                    tempVar54->value(std::to_string(scanWithPrecursor->getSelectedIonMZ().value()));
                    tempVar54->unitCvRef("MS");
                    tempVar54->unitAccession("MS:1000040");
                    tempVar54->unitName("m/z");
                    
                    //removed 18 repetitive function calls
                    auto selected_ion_cv_param = &mzML_type->run().spectrumList().get().spectrum()[i - 1].precursorList()->precursor()[0].selectedIonList()->selectedIon()[0].cvParam();
                    selected_ion_cv_param->push_back(*tempVar54);


                    // Charge State
                    if (scanWithPrecursor->getSelectedIonChargeStateGuess())
                    {
                        ms::mzml::CVParamType *tempVar55 = new ms::mzml::CVParamType("MS", "MS:1000041", "charge state");

                        tempVar55->value(std::to_string(scanWithPrecursor->getSelectedIonChargeStateGuess().value()));

                        selected_ion_cv_param->push_back(*tempVar55);

                        delete tempVar55;
                    }

                    // Selected ion intensity
                    if (scanWithPrecursor->getSelectedIonIntensity())
                    {
                        ms::mzml::CVParamType *tempVar56 = new ms::mzml::CVParamType("MS", "MS:1000042", "peak intensity");

                        tempVar56->value(std::to_string(scanWithPrecursor->getSelectedIonIntensity().value()));

                        selected_ion_cv_param->push_back(*tempVar56);

                        delete tempVar56;
                    }
                    
                    if (scanWithPrecursor->getIsolationMz() != NULL)
                    {
                        MzRange *isolationRange = scanWithPrecursor->getIsolationRange();
                        
                        ms::mzml::ParamGroupType *isolationWindowParam = new ms::mzml::ParamGroupType();
                        mzML_type->run().spectrumList().get().spectrum()[i - 1].precursorList()->precursor()[0].isolationWindow() = *isolationWindowParam;

                        //push back 3 cvparams
                        ms::mzml::CVParamType *tempVar57 = new ms::mzml::CVParamType("MS", "MS:1000827", "isolation window target m/z");

                        tempVar57->value(std::to_string(isolationRange->getMean()));
                        tempVar57->unitCvRef("MS");
                        tempVar57->unitAccession("MS:1000040");
                        tempVar57->unitName("m/z");

                        //removed 16 repetitive function calls
                        auto isolation_window_cv_param = &mzML_type->run().spectrumList().get().spectrum()[i - 1].precursorList()->precursor()[0].isolationWindow()->cvParam();
                        isolation_window_cv_param->push_back(*tempVar57);
                        ms::mzml::CVParamType *tempVar58 = new ms::mzml::CVParamType("MS", "MS:1000828", "isolation window lower offset");

                        tempVar58->value(std::to_string(isolationRange->getWidth() / 2));
                        tempVar58->unitCvRef("MS");
                        tempVar58->unitAccession("MS:1000040");
                        tempVar58->unitName("m/z");

                        isolation_window_cv_param->push_back(*tempVar58);

                        ms::mzml::CVParamType *tempVar59 = new ms::mzml::CVParamType("MS", "MS:1000829", "isolation window upper offset");

                        tempVar59->value(std::to_string(isolationRange->getWidth() / 2));
                        tempVar59->unitCvRef("MS");
                        tempVar59->unitAccession("MS:1000040");
                        tempVar59->unitName("m/z");

                        isolation_window_cv_param->push_back(*tempVar59);

                        delete tempVar59;
                        delete tempVar58;
                        delete tempVar57;
                    }
                    delete tempVar54;
                    delete tempVar53;
                    delete tempVar51;
                    delete tempVar50;
                }

                ms::mzml::CVParamType *tempVar60 = new ms::mzml::CVParamType("MS", "MS:1000511", "ms level");
                tempVar60->value(std::to_string(myMsDataFile->GetOneBasedScan(i)->getMsnOrder()));

                //removed 35 repetitive function calls
                auto spectrum_cv_param = &mzML_type->run().spectrumList().get().spectrum()[i - 1].cvParam();
                spectrum_cv_param->push_back(*tempVar60);

                ms::mzml::CVParamType *tempVar61 = new ms::mzml::CVParamType("MS", CentroidAccessions[myMsDataFile->GetOneBasedScan(i)->getIsCentroid()], CentroidNames[myMsDataFile->GetOneBasedScan(i)->getIsCentroid()]);
                tempVar61->value("");

                spectrum_cv_param->push_back(*tempVar61);

                std::string polarityName;
                std::string polarityAccession;
                std::unordered_map<Polarity, std::string>::const_iterator PolarityAccessions_iterator = PolarityAccessions.find(myMsDataFile->GetOneBasedScan(i)->getPolarity());
                std::unordered_map<Polarity, std::string>::const_iterator PolarityNames_iterator = PolarityNames.find(myMsDataFile->GetOneBasedScan(i)->getPolarity());
                if (PolarityNames_iterator != PolarityNames.end() && PolarityAccessions_iterator != PolarityAccessions.end())
                {
                    polarityName = PolarityNames_iterator->second;
                    polarityAccession = PolarityAccessions_iterator->second;
                    ms::mzml::CVParamType *tempVar62 = new ms::mzml::CVParamType("MS", polarityAccession, polarityName);

                    tempVar62->value("");

                    spectrum_cv_param->push_back(*tempVar62);

                    delete tempVar62;
                }
                else
                {
                    polarityName = PolarityNames_iterator->second;
                    polarityAccession = PolarityAccessions_iterator->second;
                }
                // Spectrum title
                if ((myMsDataFile->GetOneBasedScan(i)->getMassSpectrum()->getSize()) > 0)
                {
                    // Lowest observed mz
                    ms::mzml::CVParamType *tempVar63 = new ms::mzml::CVParamType("MS", "MS:1000528", "lowest observed m/z");

                    tempVar63->value(std::to_string(myMsDataFile->GetOneBasedScan(i)->getMassSpectrum()->getFirstX().value()));
                    tempVar63->unitCvRef("MS");
                    tempVar63->unitAccession("MS:1000040");
                    tempVar63->unitName("m/z");

                    spectrum_cv_param->push_back(*tempVar63);

                    // Highest observed mz
                    ms::mzml::CVParamType *tempVar64 = new ms::mzml::CVParamType("MS", "MS:1000527", "highest observed m/z");

                    tempVar64->value(std::to_string(myMsDataFile->GetOneBasedScan(i)->getMassSpectrum()->getLastX().value()));
                    tempVar64->unitAccession("MS:1000040");
                    tempVar64->unitName("m/z");
                    tempVar64->unitCvRef("MS");

                    spectrum_cv_param->push_back(*tempVar64);

                    delete tempVar64;
                    delete tempVar63;
                }

                // Total ion current
                ms::mzml::CVParamType *tempVar65 = new ms::mzml::CVParamType("MS", "MS:1000285", "total ion current");

                tempVar65->value(std::to_string(myMsDataFile->GetOneBasedScan(i)->getTotalIonCurrent()));

                spectrum_cv_param->push_back(*tempVar65);

                if (myMsDataFile->GetOneBasedScan(i)->getMassSpectrum()->getSize() > 0)
                {
                    //base peak m/z
                    ms::mzml::CVParamType *tempVar66 = new ms::mzml::CVParamType("MS", "MS:1000504", "base peak m/z");

                    tempVar66->value(std::to_string(myMsDataFile->GetOneBasedScan(i)->getMassSpectrum()->getXofPeakWithHighestY().value()));
                    tempVar66->unitCvRef("MS");
                    tempVar66->unitName("m/z");
                    tempVar66->unitAccession("MS:1000040");

                    spectrum_cv_param->push_back(*tempVar66);

                    //base peak intensity
                    ms::mzml::CVParamType *tempVar67 = new ms::mzml::CVParamType("MS", "MS:1000505", "base peak intensity");

                    tempVar67->value(std::to_string(myMsDataFile->GetOneBasedScan(i)->getMassSpectrum()->getYofPeakWithHighestY().value()));
                    tempVar67->unitCvRef("MS");
                    tempVar67->unitName("number of detector counts");
                    tempVar67->unitAccession("MS:1000131");

                    spectrum_cv_param->push_back(*tempVar67);

                    delete tempVar67;
                    delete tempVar66;
                }

                // Retention time
                ms::mzml::ScanListType *spectrumScanList = new ms::mzml::ScanListType(1);
                mzML_type->run().spectrumList().get().spectrum()[i - 1].scanList() = *spectrumScanList;

                ms::mzml::CVParamType *tempVar68 = new ms::mzml::CVParamType("MS", "MS:1000795", "no combination");
                tempVar68->value("");

                mzML_type->run().spectrumList().get().spectrum()[i - 1].scanList()->cvParam().push_back(*tempVar68);


                if (myMsDataFile->GetOneBasedScan(i)->getMzAnalyzer() == analyzersInThisFile[0])
                {
                    ms::mzml::ScanType *tempVar69 = new ms::mzml::ScanType();

                    //push back 3 cvparams
                    mzML_type->run().spectrumList().get().spectrum()[i - 1].scanList()->scan().push_back(*tempVar69);

                    delete tempVar69;
                }
                else
                {
                    ms::mzml::ScanType *tempVar70 = new ms::mzml::ScanType();
                    //push back 3 cvparams
                    tempVar70->instrumentConfigurationRef(analyzersInThisFileDict[myMsDataFile->GetOneBasedScan(i)->getMzAnalyzer()]);

                    mzML_type->run().spectrumList().get().spectrum()[i - 1].scanList()->scan().push_back(*tempVar70);

                    delete tempVar70;
                }
                ms::mzml::CVParamType *tempVar71 = new ms::mzml::CVParamType("MS", "MS:1000016", "scan start time");
                tempVar71->value(std::to_string(myMsDataFile->GetOneBasedScan(i)->getRetentionTime()));
                tempVar71->unitCvRef("UO");
                tempVar71->unitAccession("UO:0000031");
                tempVar71->unitName("minute");

                //removed 14 repetitive function calls
                auto spectrum_scan_cv_param = &mzML_type->run().spectrumList().get().spectrum()[i - 1].scanList()->scan()[0].cvParam();
                spectrum_scan_cv_param->push_back(*tempVar71);

                ms::mzml::CVParamType *tempVar72 = new ms::mzml::CVParamType("MS", "MS:1000512", "filter string");

                tempVar72->value(myMsDataFile->GetOneBasedScan(i)->getScanFilter());

                spectrum_scan_cv_param->push_back(*tempVar72);

                if (myMsDataFile->GetOneBasedScan(i)->getInjectionTime())
                {
                    ms::mzml::CVParamType *tempVar73 = new ms::mzml::CVParamType("MS", "MS:1000927", "ion injection time");
                    tempVar73->value(std::to_string(myMsDataFile->GetOneBasedScan(i)->getInjectionTime().value()));
                    tempVar73->unitName("millisecond");
                    tempVar73->unitAccession("UO:0000028");
                    tempVar73->unitCvRef("UO");

                    spectrum_scan_cv_param->push_back(*tempVar73);

                    delete tempVar73;
                }

                if (myMsDataFile->GetOneBasedScan(i)->getMsnOrder() != 1)
                {
                    auto scanWithPrecursor = myMsDataFile->GetOneBasedScan(i);
                    if (scanWithPrecursor->getSelectedIonMonoisotopicGuessMz())
                    {

                        ms::mzml::UserParamType *tempVar74 = new ms::mzml::UserParamType("[mzLib]Monoisotopic M/Z:");

                        tempVar74->value(std::to_string(scanWithPrecursor->getSelectedIonMonoisotopicGuessMz().value()));

                        mzML_type->run().spectrumList().get().spectrum()[i - 1].scanList()->scan()[0].userParam().push_back(*tempVar74);

                        delete tempVar74;
                    }
                }


                ms::mzml::ScanWindowListType *spectrumScanWindow = new ms::mzml::ScanWindowListType(1);
                 mzML_type->run().spectrumList().get().spectrum()[i - 1].scanList()->scan()[0].scanWindowList(*spectrumScanWindow);

                ms::mzml::ParamGroupType *tempVar75 = new ms::mzml::ParamGroupType();

                mzML_type->run().spectrumList().get().spectrum()[i - 1].scanList()->scan()[0].scanWindowList()->scanWindow().push_back(*tempVar75);

                ms::mzml::CVParamType *tempVar76 = new ms::mzml::CVParamType("MS", "MS:1000501", "scan window lower limit");
                tempVar76->value(std::to_string(myMsDataFile->GetOneBasedScan(i)->getScanWindowRange()->getMinimum()));
                tempVar76->unitCvRef("MS");
                tempVar76->unitAccession("MS:1000040");
                tempVar76->unitName("m/z");

                mzML_type->run().spectrumList().get().spectrum()[i - 1].scanList()->scan()[0].scanWindowList()->scanWindow()[0].cvParam().push_back(*tempVar76);
                
                ms::mzml::CVParamType *tempVar77 = new ms::mzml::CVParamType("MS", "MS:1000500", "scan window upper limit");
                tempVar77->value(std::to_string(myMsDataFile->GetOneBasedScan(i)->getScanWindowRange()->getMaximum()));
                tempVar77->unitCvRef("MS");
                tempVar77->unitAccession("MS:1000040");
                tempVar77->unitName("m/z");

                mzML_type->run().spectrumList().get().spectrum()[i - 1].scanList()->scan()[0].scanWindowList()->scanWindow()[0].cvParam().push_back(*tempVar77);
                if (myMsDataFile->GetOneBasedScan(i)->getNoiseData().empty())
                {

                    ms::mzml::BinaryDataArrayListType *spectrumBinDataList = new ms::mzml::BinaryDataArrayListType(2);
                    mzML_type->run().spectrumList().get().spectrum()[i - 1].binaryDataArrayList(*spectrumBinDataList);
                }

                if (!myMsDataFile->GetOneBasedScan(i)->getNoiseData().empty())
                {

                    ms::mzml::BinaryDataArrayListType *spectrumBinDataList = new ms::mzml::BinaryDataArrayListType(5);
                    mzML_type->run().spectrumList().get().spectrum()[i - 1].binaryDataArrayList(*spectrumBinDataList);
                }

                std::vector<unsigned char> XArrayVec = myMsDataFile->GetOneBasedScan(i)->getMassSpectrum()->Get64BitXarray();
				unsigned char XArray[XArrayVec.size()];
				std::copy(XArrayVec.begin(), XArrayVec.end(), XArray);
				xml_schema::base64_binary binary_64bitXArray((void*)XArray, (sizeof(XArray)/sizeof(*XArray)));  

                ms::mzml::BinaryDataArrayType *tempVar78 = new ms::mzml::BinaryDataArrayType(binary_64bitXArray, (size_t)(4 * (double)ceil((static_cast<double>(binary_64bitXArray.encode().length()) / 3))));

                mzML_type->run().spectrumList().get().spectrum()[i - 1].binaryDataArrayList().get().binaryDataArray().push_back(*tempVar78);

                ms::mzml::CVParamType *tempVar79 = new ms::mzml::CVParamType("MS", "MS:1000514", "m/z array");
                tempVar79->unitName("m/z");
                tempVar79->value("");
                tempVar79->unitCvRef("MS");
                tempVar79->unitAccession("MS:1000040");

                //removed 16 repetitive function calls
                auto binary_data_cv_param = &mzML_type->run().spectrumList().get().spectrum()[i - 1].binaryDataArrayList().get().binaryDataArray()[0].cvParam();
                binary_data_cv_param->push_back(*tempVar79);

                ms::mzml::CVParamType *tempVar80 = new ms::mzml::CVParamType("MS", "MS:1000523", "64-bit float");
                tempVar80->value("");

                binary_data_cv_param->push_back(*tempVar80);

                ms::mzml::CVParamType *tempVar81 = new ms::mzml::CVParamType("MS", "MS:1000576", "no compression");
                tempVar81->value("");

                binary_data_cv_param->push_back(*tempVar81);

                std::vector<unsigned char> YArrayVec = myMsDataFile->GetOneBasedScan(i)->getMassSpectrum()->Get64BitYarray();
				unsigned char YArray[YArrayVec.size()];
				std::copy(YArrayVec.begin(), YArrayVec.end(), YArray);
				xml_schema::base64_binary binary_64bitYArray((void*)YArray, (sizeof(YArray)/sizeof(*YArray)));  

                ms::mzml::BinaryDataArrayType *tempVar82 = new ms::mzml::BinaryDataArrayType(binary_64bitYArray, (size_t)(4 * (double)ceil((static_cast<double>(binary_64bitYArray.encode().length()) / 3))));

                mzML_type->run().spectrumList().get().spectrum()[i - 1].binaryDataArrayList().get().binaryDataArray().push_back(*tempVar82);

                //push back 3 cvparams
                ms::mzml::CVParamType *tempVar83 = new ms::mzml::CVParamType("MS", "MS:1000515", "intensity array");
                tempVar83->unitCvRef("MS");
                tempVar83->unitAccession("MS:1000131");
                tempVar83->unitName("number of counts");
                tempVar83->value("");

                //removed 16 repetitive function calls
                binary_data_cv_param = &mzML_type->run().spectrumList().get().spectrum()[i - 1].binaryDataArrayList().get().binaryDataArray()[1].cvParam();
                binary_data_cv_param->push_back(*tempVar83);

                ms::mzml::CVParamType *tempVar84 = new ms::mzml::CVParamType("MS", "MS:1000523", "64-bit float");
                tempVar84->value("");

                binary_data_cv_param->push_back(*tempVar84);

                ms::mzml::CVParamType *tempVar85 = new ms::mzml::CVParamType("MS", "MS:1000576", "no compression");
                tempVar85->value("");

                binary_data_cv_param->push_back(*tempVar85);

                if (!myMsDataFile->GetOneBasedScan(i)->getNoiseData().empty())
                {
                    // mass
                    std::vector<unsigned char> noiseDataMassVec = myMsDataFile->GetOneBasedScan(i)->Get64BitNoiseDataMass();
                    unsigned char noiseDataMass[noiseDataMassVec.size()]; 
                    std::copy(noiseDataMassVec.begin(), noiseDataMassVec.end(), noiseDataMass);
                    xml_schema::base64_binary binary_noiseDataMass((void*)noiseDataMass, (sizeof(noiseDataMass)/sizeof(*noiseDataMass)));  

                    ms::mzml::BinaryDataArrayType *tempVar86 = new ms::mzml::BinaryDataArrayType(binary_noiseDataMass, (size_t)(4 * (double)ceil((static_cast<double>(binary_noiseDataMass.encode().length()) / 3))));

                    //removed 140 repetitive function calls
                    auto bin_data_array = mzML_type->run().spectrumList().get().spectrum()[i - 1].binaryDataArrayList().get().binaryDataArray();
                    bin_data_array.push_back(*tempVar86);
                    bin_data_array[2].arrayLength() = bin_data_array[2].binary().encode().length() / 8;

                    ms::mzml::CVParamType *tempVar87 = new ms::mzml::CVParamType("MS", "MS:1000786", "non-standard data array");
                    tempVar87->value("mass");
                    tempVar87->unitCvRef("MS");

                    bin_data_array[2].cvParam().push_back(*tempVar87);

                    ms::mzml::CVParamType *tempVar88 = new ms::mzml::CVParamType("MS", "MS:1000523", "64-bit float");
                    tempVar88->value("");

                    bin_data_array[2].cvParam().push_back(*tempVar88);

                    ms::mzml::CVParamType *tempVar89 = new ms::mzml::CVParamType("MS", "MS:1000576", "no compression");
                    tempVar89->value("");

                    bin_data_array[2].cvParam().push_back(*tempVar89);

                    //push back 1 user param
                    ms::mzml::UserParamType *tempVar90 = new ms::mzml::UserParamType("kelleherCustomType");
                    tempVar90->value("noise m/z");

                    bin_data_array[2].userParam().push_back(*tempVar90);

                    // noise
                    std::vector<unsigned char> noiseDataNoiseVec = myMsDataFile->GetOneBasedScan(i)->Get64BitNoiseDataNoise();
                    unsigned char noiseDataNoise[noiseDataNoiseVec.size()]; 
                    std::copy(noiseDataNoiseVec.begin(), noiseDataNoiseVec.end(), noiseDataNoise);
                    xml_schema::base64_binary binary_noiseDataNoise((void*)noiseDataNoise, (sizeof(noiseDataNoise)/sizeof(*noiseDataNoise)));  

                    ms::mzml::BinaryDataArrayType *tempVar91 = new ms::mzml::BinaryDataArrayType(binary_noiseDataNoise, (size_t)(4 * (double)ceil((static_cast<double>(binary_noiseDataNoise.encode().length()) / 3))));
                    bin_data_array.push_back(*tempVar91);

                    bin_data_array[3].arrayLength() = bin_data_array[3].binary().encode().length() / 8;

                    ms::mzml::CVParamType *tempVar92 = new ms::mzml::CVParamType("MS", "MS:1000786", "non-standard data array");
                    tempVar92->value("SignalToNoise");

                    bin_data_array[3].cvParam().push_back(*tempVar92);

                    ms::mzml::CVParamType *tempVar93 = new ms::mzml::CVParamType("MS", "MS:1000523", "64-bit float");
                    tempVar93->value("");

                    bin_data_array[3].cvParam().push_back(*tempVar93);

                    ms::mzml::CVParamType *tempVar94 = new ms::mzml::CVParamType("MS", "MS:1000576", "no compression");
                    tempVar94->value("");

                    bin_data_array[3].cvParam().push_back(*tempVar94);

                    //push back 1 user param
                    ms::mzml::UserParamType *tempVar95 = new ms::mzml::UserParamType("kelleherCustomType");
                    tempVar95->value("noise baseline");
                    bin_data_array[3].userParam().push_back(*tempVar95);

                    // baseline
                    std::vector<unsigned char> noiseDataBaselineVec = myMsDataFile->GetOneBasedScan(i)->Get64BitNoiseDataBaseline();
                    unsigned char noiseDataBaseline[noiseDataBaselineVec.size()]; 
                    std::copy(noiseDataBaselineVec.begin(), noiseDataBaselineVec.end(), noiseDataBaseline);
                    xml_schema::base64_binary binary_noiseDataBaseline((void*)noiseDataBaseline, (sizeof(noiseDataBaseline)/sizeof(*noiseDataBaseline))); 

                    ms::mzml::BinaryDataArrayType *tempVar96 = new ms::mzml::BinaryDataArrayType(binary_noiseDataBaseline, (size_t)(4 * (double)ceil((static_cast<double>(binary_noiseDataBaseline.encode().length()) / 3))));
                    bin_data_array.push_back(*tempVar96);
                    bin_data_array[4].arrayLength() = bin_data_array[4].binary().encode().length() / 8;

                    ms::mzml::CVParamType *tempVar97 = new ms::mzml::CVParamType("MS", "MS:1000786", "non-standard data array");
                    tempVar97->value("baseline");

                    bin_data_array[4].cvParam().push_back(*tempVar97);

                    ms::mzml::CVParamType *tempVar98 = new ms::mzml::CVParamType("MS", "MS:1000523", "64-bit float");
                    tempVar98->value("");

                    bin_data_array[4].cvParam().push_back(*tempVar98);

                    ms::mzml::CVParamType *tempVar99 = new ms::mzml::CVParamType("MS", "MS:1000576", "no compression");
                    tempVar99->value("");

                    bin_data_array[4].cvParam().push_back(*tempVar99);

                    //push back 1 user param
                    ms::mzml::UserParamType *tempVar100 = new ms::mzml::UserParamType("kelleherCustomType");
                    tempVar100->value("noise intensity");

                    bin_data_array[4].userParam().push_back(*tempVar100);

                    //set binary data array
                    mzML_type->run().spectrumList().get().spectrum()[i - 1].binaryDataArrayList().get().binaryDataArray(bin_data_array);

                    delete tempVar100;
                    delete tempVar99;
                    delete tempVar98;
                    delete tempVar97;
                    delete tempVar96;
                    delete tempVar95;
                    delete tempVar94;
                    delete tempVar93;
                    delete tempVar92;
                    delete tempVar91;
                    delete tempVar90;
                    delete tempVar89;
                    delete tempVar88;
                    delete tempVar87;
                    delete tempVar86;
                }

                delete tempVar85;
                delete tempVar84;
                delete tempVar83;
                delete tempVar82;
                delete tempVar81;
                delete tempVar80;
                delete tempVar79;
                delete tempVar78;
                delete tempVar77;
                delete tempVar76;
                delete tempVar75;
                delete tempVar72;
                delete tempVar71;
                delete tempVar68;
                delete tempVar65;
                delete tempVar61;
                delete tempVar60;
                delete tempVar47;
            }

            if (!writeIndexed)
            {
                xml_schema::namespace_infomap map;
                map[""].name = "http://psi.hupo.org/ms/mzml";
                map[""].schema = "/home/nrbiddle/mzlib-c/MzML/XSD/mzML1.1.0.xsd";

                // Serialize to a file.
                try{
                    std::ofstream ofs (outputFile);
                    mzML (ofs, *mzML_type, map);
                    ofs.close();
                }

                catch (const xml_schema::exception& e)
                {
                    std::cerr << e << std::endl;
                }         

            }
            else if (writeIndexed)
            {
                auto inMemoryTextWriter = std::ostringstream();

                //compute total offset

                xml_schema::namespace_infomap map;
                map[""].name = "http://psi.hupo.org/ms/mzml";
                map[""].schema = "/home/nrbiddle/mzlib-c/MzML/XSD/mzML1.1.0.xsd";

                // Serialize to a file.
                try{
                    mzML (inMemoryTextWriter, *mzML_type, map);
                }

                catch (const xml_schema::exception& e)
                {
                    std::cerr << e << std::endl;
                }   

                std::string allmzMLData = StringHelper::replace(inMemoryTextWriter.str(), "\r\n", "\n");

                std::optional<long long> indexListOffset = std::make_optional(allmzMLData.length());

                //new stream with correct formatting
                //push back two indexes
                ms::mzml::IndexListType *tempVar101 = new ms::mzml::IndexListType(2);

                //starts as spectrum be defualt
                auto indexname = ms::mzml::name(ms::mzml::name::value::spectrum);

                //spectra naming
                ms::mzml::IndexType *tempVar102 = new ms::mzml::IndexType(indexname);
                tempVar101->index().push_back(*tempVar102);

                //switch to chromatogram name
                indexname = ms::mzml::name::value::chromatogram;

                //chroma naming
                ms::mzml::IndexType *tempVar103 = new ms::mzml::IndexType(indexname);
                tempVar101->index().push_back(*tempVar103);

                int numScans = myMsDataFile->getNumSpectra();
 
                int numChromas = mzML_type->run().chromatogramList()->count();

                //now calculate offsets of each scan and chroma

                //add spectra offsets
                // indexedMzml->indexList()->index()[0]->offset() = std::vector<ms::mzml::OffsetType*>(numScans);
                //add chroma offsets
                // indexedMzml->indexList()->index()[1]->offset() = std::vector<ms::mzml::OffsetType*>(numChromas);

                //compute checksum
                std::string chksum = "Dummy";

                ms::mzml::indexedmzML *indexedMzml = new ms::mzml::indexedmzML(*mzML_type, *tempVar101, indexListOffset.value(), chksum);

                int i = 0;
                int a = 1;
                int index;
                //indexOf search returns location fom beginning of line (3 characters short)
                int offsetFromBeforeScanTag = 3;
                //spectra offset loop
                while (i < numScans)
                {
                    index = (int)allmzMLData.find(mzML_type->run().spectrumList().get().spectrum()[i].id(), (a - 1));
                    if (index != -1)
                    {
                        a = index;

                        ms::mzml::OffsetType *tempVar104 = new ms::mzml::OffsetType(a + offsetFromBeforeScanTag, mzML_type->run().spectrumList().get().spectrum()[i].id());
                        indexedMzml->indexList().index()[0].offset().push_back(*tempVar104);
                        i++;

                        delete tempVar104;
                    }
                }
                int offsetFromBeforeChromaTag = 3;
                index = (int)allmzMLData.find("id=\"" + mzML_type->run().chromatogramList()->chromatogram()[0].id() + "\"", (a - 1));
                if (index != -1)
                {
                    a = index;

                    ms::mzml::OffsetType *tempVar105 = new ms::mzml::OffsetType(a + offsetFromBeforeChromaTag, mzML_type->run().chromatogramList()->chromatogram()[0].id());

                    indexedMzml->indexList().index()[1].offset().push_back(*tempVar105);

                    delete tempVar105;
                }
                //offset
                int offsetFromNullIndexList = 32;

                indexedMzml->indexListOffset(indexListOffset.value() - offsetFromNullIndexList);

                indexedMzml->fileChecksum(chksum);

                inMemoryTextWriter.str("");
                inMemoryTextWriter.clear();

                xml_schema::namespace_infomap indexed_map;
                indexed_map[""].name = "http://psi.hupo.org/ms/mzml";
                indexed_map[""].schema = "/home/nrbiddle/mzlib-c/MzML/XSD/mzML1.1.1_idx.xsd";

                // Serialize to a file.
                try{
                    indexedmzML_ (inMemoryTextWriter, *indexedMzml, indexed_map);
                }

                catch (const xml_schema::exception& e)
                {
                    std::cerr << e << std::endl;
                }   

                std::string indexedMzmlwithBlankChecksumStream = inMemoryTextWriter.str();

                std::string indexedMzmlwithBlankChecksumString = indexedMzmlwithBlankChecksumStream.substr(0, (int)indexedMzmlwithBlankChecksumStream.find("<fileChecksum>", (a - 1)));

                inMemoryTextWriter.str("");
                inMemoryTextWriter.clear();

                inMemoryTextWriter << indexedMzmlwithBlankChecksumString;

                chksum = std::to_string(StringHelper::GetHashCode(inMemoryTextWriter.str()));

                chksum = StringHelper::replace(chksum, "-", "");
                chksum = StringHelper::toLower(chksum);
                indexedMzml->fileChecksum(chksum);

                // Serialize to a file.
                try{
                    std::ofstream ofs (outputFile);
                    indexedmzML_ (ofs, *indexedMzml, indexed_map);
                    ofs.close();
                }

                catch (const xml_schema::exception& e)
                {
                    std::cerr << e << std::endl;
                }      


                delete tempVar103;
                delete tempVar102;
            }

            delete tempVar45;
            delete tempVar44;
            delete tempVar43;
            delete tempVar42;
            delete tempVar41;
            delete tempVar40;
            delete tempVar39;
            delete tempVar38;
            delete tempVar37;
            delete tempVar35;
            delete tempVar32;
            delete tempVar31;
            delete tempVar30;
            delete tempVar18;
            delete tempVar17;
            delete tempVar15;
            delete tempVar14;
            delete tempVar4;
            delete tempVar3;
        }
    }
}
