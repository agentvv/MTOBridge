#pragma once

#include "MatlabTypesInterface.hpp"
#include <map>

std::vector<matlab::data::Array> Concerned_section_one_span_moment(std::shared_ptr<MATLABControllerType> _matlabPtr, matlab::data::Array arg1, matlab::data::Array arg2, matlab::data::Array arg3, matlab::data::Array arg4, matlab::data::Array arg5, matlab::data::Array arg6, matlab::data::Array arg7) { 
    matlab::data::ArrayFactory _arrayFactory;
    std::vector<matlab::data::Array> _args = {
        arg1,
        arg2,
        arg3,
        arg4,
        arg5,
        arg6,
        arg7 };
    std::vector<matlab::data::Array> _result = _matlabPtr->feval(u"Concerned_section_one_span_moment", 4, _args);
    return _result;
}



std::vector<matlab::data::Array> Concerned_section_one_span_shear(std::shared_ptr<MATLABControllerType> _matlabPtr, matlab::data::Array arg1, matlab::data::Array arg2, matlab::data::Array arg3, matlab::data::Array arg4, matlab::data::Array arg5, matlab::data::Array arg6, matlab::data::Array arg7) { 
    matlab::data::ArrayFactory _arrayFactory;
    std::vector<matlab::data::Array> _args = {
        arg1,
        arg2,
        arg3,
        arg4,
        arg5,
        arg6,
        arg7 };
    std::vector<matlab::data::Array> _result = _matlabPtr->feval(u"Concerned_section_one_span_shear", 4, _args);
    return _result;
}



std::vector<matlab::data::Array> Concerned_section_three_span_moment(std::shared_ptr<MATLABControllerType> _matlabPtr, matlab::data::Array arg1, matlab::data::Array arg2, matlab::data::Array arg3, matlab::data::Array arg4, matlab::data::Array arg5, matlab::data::Array arg6, matlab::data::Array arg7) { 
    matlab::data::ArrayFactory _arrayFactory;
    std::vector<matlab::data::Array> _args = {
        arg1,
        arg2,
        arg3,
        arg4,
        arg5,
        arg6,
        arg7 };
    std::vector<matlab::data::Array> _result = _matlabPtr->feval(u"Concerned_section_three_span_moment", 6, _args);
    return _result;
}



std::vector<matlab::data::Array> Concerned_section_three_span_shear(std::shared_ptr<MATLABControllerType> _matlabPtr, matlab::data::Array arg1, matlab::data::Array arg2, matlab::data::Array arg3, matlab::data::Array arg4, matlab::data::Array arg5, matlab::data::Array arg6, matlab::data::Array arg7) { 
    matlab::data::ArrayFactory _arrayFactory;
    std::vector<matlab::data::Array> _args = {
        arg1,
        arg2,
        arg3,
        arg4,
        arg5,
        arg6,
        arg7 };
    std::vector<matlab::data::Array> _result = _matlabPtr->feval(u"Concerned_section_three_span_shear", 4, _args);
    return _result;
}



std::vector<matlab::data::Array> Concerned_section_two_span_moment(std::shared_ptr<MATLABControllerType> _matlabPtr, matlab::data::Array arg1, matlab::data::Array arg2, matlab::data::Array arg3, matlab::data::Array arg4, matlab::data::Array arg5, matlab::data::Array arg6, matlab::data::Array arg7) { 
    matlab::data::ArrayFactory _arrayFactory;
    std::vector<matlab::data::Array> _args = {
        arg1,
        arg2,
        arg3,
        arg4,
        arg5,
        arg6,
        arg7 };
    std::vector<matlab::data::Array> _result = _matlabPtr->feval(u"Concerned_section_two_span_moment", 6, _args);
    return _result;
}



std::vector<matlab::data::Array> Concerned_section_two_span_shear(std::shared_ptr<MATLABControllerType> _matlabPtr, matlab::data::Array arg1, matlab::data::Array arg2, matlab::data::Array arg3, matlab::data::Array arg4, matlab::data::Array arg5, matlab::data::Array arg6, matlab::data::Array arg7) { 
    matlab::data::ArrayFactory _arrayFactory;
    std::vector<matlab::data::Array> _args = {
        arg1,
        arg2,
        arg3,
        arg4,
        arg5,
        arg6,
        arg7 };
    std::vector<matlab::data::Array> _result = _matlabPtr->feval(u"Concerned_section_two_span_shear", 4, _args);
    return _result;
}



std::vector<matlab::data::Array> Critical_section_one_span_moment(std::shared_ptr<MATLABControllerType> _matlabPtr, matlab::data::Array arg1, matlab::data::Array arg2, matlab::data::Array arg3, matlab::data::Array arg4, matlab::data::Array arg5, matlab::data::Array arg6, matlab::data::Array arg7) { 
    matlab::data::ArrayFactory _arrayFactory;
    std::vector<matlab::data::Array> _args = {
        arg1,
        arg2,
        arg3,
        arg4,
        arg5,
        arg6,
        arg7 };
    std::vector<matlab::data::Array> _result = _matlabPtr->feval(u"Critical_section_one_span_moment", 7, _args);
    return _result;
}



std::vector<matlab::data::Array> Critical_section_one_span_shear(std::shared_ptr<MATLABControllerType> _matlabPtr, matlab::data::Array arg1, matlab::data::Array arg2, matlab::data::Array arg3, matlab::data::Array arg4, matlab::data::Array arg5, matlab::data::Array arg6, matlab::data::Array arg7) { 
    matlab::data::ArrayFactory _arrayFactory;
    std::vector<matlab::data::Array> _args = {
        arg1,
        arg2,
        arg3,
        arg4,
        arg5,
        arg6,
        arg7 };
    std::vector<matlab::data::Array> _result = _matlabPtr->feval(u"Critical_section_one_span_shear", 7, _args);
    return _result;
}



std::vector<matlab::data::Array> Critical_section_three_span_negative_moment(std::shared_ptr<MATLABControllerType> _matlabPtr, matlab::data::Array arg1, matlab::data::Array arg2, matlab::data::Array arg3, matlab::data::Array arg4, matlab::data::Array arg5, matlab::data::Array arg6, matlab::data::Array arg7) { 
    matlab::data::ArrayFactory _arrayFactory;
    std::vector<matlab::data::Array> _args = {
        arg1,
        arg2,
        arg3,
        arg4,
        arg5,
        arg6,
        arg7 };
    std::vector<matlab::data::Array> _result = _matlabPtr->feval(u"Critical_section_three_span_negative_moment", 7, _args);
    return _result;
}



std::vector<matlab::data::Array> Critical_section_three_span_positive_moment(std::shared_ptr<MATLABControllerType> _matlabPtr, matlab::data::Array arg1, matlab::data::Array arg2, matlab::data::Array arg3, matlab::data::Array arg4, matlab::data::Array arg5, matlab::data::Array arg6, matlab::data::Array arg7) { 
    matlab::data::ArrayFactory _arrayFactory;
    std::vector<matlab::data::Array> _args = {
        arg1,
        arg2,
        arg3,
        arg4,
        arg5,
        arg6,
        arg7 };
    std::vector<matlab::data::Array> _result = _matlabPtr->feval(u"Critical_section_three_span_positive_moment", 7, _args);
    return _result;
}



std::vector<matlab::data::Array> Critical_section_three_span_shear(std::shared_ptr<MATLABControllerType> _matlabPtr, matlab::data::Array arg1, matlab::data::Array arg2, matlab::data::Array arg3, matlab::data::Array arg4, matlab::data::Array arg5, matlab::data::Array arg6, matlab::data::Array arg7) { 
    matlab::data::ArrayFactory _arrayFactory;
    std::vector<matlab::data::Array> _args = {
        arg1,
        arg2,
        arg3,
        arg4,
        arg5,
        arg6,
        arg7 };
    std::vector<matlab::data::Array> _result = _matlabPtr->feval(u"Critical_section_three_span_shear", 7, _args);
    return _result;
}



std::vector<matlab::data::Array> Critical_section_two_span_negative_moment(std::shared_ptr<MATLABControllerType> _matlabPtr, matlab::data::Array arg1, matlab::data::Array arg2, matlab::data::Array arg3, matlab::data::Array arg4, matlab::data::Array arg5, matlab::data::Array arg6, matlab::data::Array arg7) { 
    matlab::data::ArrayFactory _arrayFactory;
    std::vector<matlab::data::Array> _args = {
        arg1,
        arg2,
        arg3,
        arg4,
        arg5,
        arg6,
        arg7 };
    std::vector<matlab::data::Array> _result = _matlabPtr->feval(u"Critical_section_two_span_negative_moment", 7, _args);
    return _result;
}



std::vector<matlab::data::Array> Critical_section_two_span_positive_moment(std::shared_ptr<MATLABControllerType> _matlabPtr, matlab::data::Array arg1, matlab::data::Array arg2, matlab::data::Array arg3, matlab::data::Array arg4, matlab::data::Array arg5, matlab::data::Array arg6, matlab::data::Array arg7) { 
    matlab::data::ArrayFactory _arrayFactory;
    std::vector<matlab::data::Array> _args = {
        arg1,
        arg2,
        arg3,
        arg4,
        arg5,
        arg6,
        arg7 };
    std::vector<matlab::data::Array> _result = _matlabPtr->feval(u"Critical_section_two_span_positive_moment", 7, _args);
    return _result;
}



std::vector<matlab::data::Array> Critical_section_two_span_shear(std::shared_ptr<MATLABControllerType> _matlabPtr, matlab::data::Array arg1, matlab::data::Array arg2, matlab::data::Array arg3, matlab::data::Array arg4, matlab::data::Array arg5, matlab::data::Array arg6, matlab::data::Array arg7) { 
    matlab::data::ArrayFactory _arrayFactory;
    std::vector<matlab::data::Array> _args = {
        arg1,
        arg2,
        arg3,
        arg4,
        arg5,
        arg6,
        arg7 };
    std::vector<matlab::data::Array> _result = _matlabPtr->feval(u"Critical_section_two_span_shear", 7, _args);
    return _result;
}