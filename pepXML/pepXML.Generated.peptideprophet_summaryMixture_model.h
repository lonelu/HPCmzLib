﻿#pragma once

#include <string>
#include <vector>
#include <any>

//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.42000
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------


namespace pepXML
{
    namespace Generated
    {
        /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "4.7.2046.0")][System.SerializableAttribute()][System.Diagnostics.DebuggerStepThroughAttribute()][System.ComponentModel.DesignerCategoryAttribute("code")][System.Xml.Serialization.XmlTypeAttribute(AnonymousType = true, Namespace = "http://regis-web.systemsbiology.net/pepXML")] public partial class peptideprophet_summaryMixture_model
        class peptideprophet_summaryMixture_model
        {

        private:
            std::vector<std::any> itemsField;

            std::string precursor_ion_chargeField;

            std::string commentsField;

            float prior_probabilityField = 0;

            float est_tot_correctField = 0;

            std::string tot_num_spectraField;

            std::string num_iterationsField;

            /// <remarks/>
        public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlElementAttribute("mixturemodel", typeof(peptideprophet_summaryMixture_modelMixturemodel))][System.Xml.Serialization.XmlElementAttribute("mixturemodel_distribution", typeof(peptideprophet_summaryMixture_modelMixturemodel_distribution))] public object[] Items
            std::vector<std::any> getItems() const;
            void setItems(const std::vector<std::any> &value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute(DataType = "nonNegativeInteger")] public string precursor_ion_charge
            std::string getprecursor_ion_charge() const;
            void setprecursor_ion_charge(const std::string &value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute()] public string comments
            std::string getcomments() const;
            void setcomments(const std::string &value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute()] public float prior_probability
            float getprior_probability() const;
            void setprior_probability(float value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute()] public float est_tot_correct
            float getest_tot_correct() const;
            void setest_tot_correct(float value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute(DataType = "nonNegativeInteger")] public string tot_num_spectra
            std::string gettot_num_spectra() const;
            void settot_num_spectra(const std::string &value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute(DataType = "nonNegativeInteger")] public string num_iterations
            std::string getnum_iterations() const;
            void setnum_iterations(const std::string &value);
        };
    }
}
