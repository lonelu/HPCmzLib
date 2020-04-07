﻿#pragma once

#include <string>
#include <vector>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace pepXML { namespace Generated { class ptmprophet_resultMod_aminoacid_probability; } }

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
//ORIGINAL LINE: [System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "4.7.2046.0")][System.SerializableAttribute()][System.Diagnostics.DebuggerStepThroughAttribute()][System.ComponentModel.DesignerCategoryAttribute("code")][System.Xml.Serialization.XmlTypeAttribute(AnonymousType = true, Namespace = "http://regis-web.systemsbiology.net/pepXML")][System.Xml.Serialization.XmlRootAttribute(Namespace = "http://regis-web.systemsbiology.net/pepXML", IsNullable = false)] public partial class ptmprophet_result
        class ptmprophet_result
        {

        private:
            std::vector<ptmprophet_resultMod_aminoacid_probability*> mod_aminoacid_probabilityField;

            float priorField = 0;

            std::string ptmField;

            std::string ptm_peptideField;

            /// <remarks/>
        public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlElementAttribute("mod_aminoacid_probability")] public ptmprophet_resultMod_aminoacid_probability[] mod_aminoacid_probability
            std::vector<ptmprophet_resultMod_aminoacid_probability*> getmod_aminoacid_probability() const;
            void setmod_aminoacid_probability(const std::vector<ptmprophet_resultMod_aminoacid_probability*> &value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute()] public float prior
            float getprior() const;
            void setprior(float value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute()] public string ptm
            std::string getptm() const;
            void setptm(const std::string &value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute()] public string ptm_peptide
            std::string getptm_peptide() const;
            void setptm_peptide(const std::string &value);
        };
    }
}
