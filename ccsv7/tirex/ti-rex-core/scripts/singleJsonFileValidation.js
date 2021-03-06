'use strict';
const fs = require('fs');
require('rootpath')();
const jsonlint = require('jsonlint');
const jsonValidator = require('jsonschema').Validator;
const schema = require('scripts/metadataSchema');

/**
 * Maps the generated error messages to a message more comprehensive
 */

const errorCases = {
    'does not match pattern "^[^/][^:](.)*(.[^/]+)$"': 'is not a relative path',
    'does not match pattern "^(ccs|iar|keil)$"': 'is not one of "css", "iar", "keil"',
    'does not match pattern "^(macros|linux|win)$': 'is not one of "macros", "linux", "win"',
    'does not match pattern "^(tirtos|freertos)$"': 'is not one of "tirtos", "freertos"',
    'does not match pattern "^(english|chinese)$"': 'is not one of "english", "chinese"',
    'does not match pattern "^(ccs|gcc|iar)$"': 'is not one of "ccs", "gcc", "iar"',
    'does not match pattern "^(board|ide|probe|programmer|utility)$"': 'is not one of "board", "ide", "probe","programmer","utility"',
    'does not match pattern "^(project.ccs|protject.energia|project.iar|project.keil|file|file.importable|file.executable|folder|folder.importable|web.page|web.app|categoryInfo|other)$"': 'is not one of the accepted resourceType',
    'does not match pattern "^((.+)[/]([^/]+)|(http(s)?:\\/\\/.)?(www\\.)?[-a-zA-Z0-9@:%._\\+~#=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%_\\+.~#?&//=]*))$"': 'is not a path or a url',
    'does not match pattern "^(http(s)?:\\/\\/.)?(www\\.)?[-a-zA-Z0-9@:%._\\+~#=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%_\\+.~#?&//=]*)$"': 'is not a url',
    'does not match pattern "^(device|family|subfamily)$"': 'is not one of "device", "family", "subfamily"',
    'does not match pattern "^([0-9][.][0-9]{1,2}[.][0-9]{1,2})$"': 'is not in the form of "x.xx.xx"',
    'does not match pattern "^([0-9]{1,2}[.][0-9]{1,2}[.][0-9]{1,2})([.].*)?"': 'is not a valid package version',
    'does not match pattern "^[.][^.]+$': 'is not a file extension',
    'does not match pattern "^(devices|devtools|software)$"': 'is not one of "devices", "devtools", "software"'
};


/**
 * Gets the error message based on the error message generated by jsonschema
 * @param {string} message - error message generated by jsonschema
 */
function getErrorMessage(message) {
    var errorMessage = errorCases[message];
    if (errorMessage) {
        return errorMessage;
    }else {
        return message;
    }
}

/**
 * Gathers information about the instance that is invalid
 * @param {string} filetype - type of metadata eg: devices, content,package
 * @param {object} errorInstance - the instance in the json that is invalid
 */
function getErrorInfo(filetype, errorInstance) {
    var errorInfo = {};
    if (filetype === 'content') {
        errorInfo.name = errorInstance.name;
        errorInfo.categories = errorInstance.categories;
    } else {
        errorInfo.id = errorInstance.id;
        errorInfo.name = errorInstance.name;
    }
    return errorInfo;
}

/**
 * Validates json schema and output the errors
 * @param {JSON} json - the json to be validated
 * @param {object} schema - the schema to be validated against
 * @param {object} validator - the validator
 * @param {string} filetype - type of metadata eg: devices, content,package
 */
function validate(json, schema, validator,filetype) {
    var errors = validator.validate(json, schema).errors;
    if (errors.length > 0 ) {
        for (var i = 0; i < errors.length; i++) {
            var property = errors[i].property.split('.');
            var instance = property[0];
            var errorInfo = getErrorInfo(filetype, json[instance[instance.length - 2]]);
            var errorString = JSON.stringify(errorInfo);
            if (property.length > 1) {
                errorString += "." + property[1];
            }
            errorString += " " + getErrorMessage(errors[i].message);
            console.log(errorString);
        }
    }else{
        console.log('Valid!');
    }
}

/**
 * Validates package.tirex.json
 */
function validatePackageJson(json) {
    var validator = new jsonValidator();
    validator.addSchema(schema.packageVersion, '/PackageVersion');
    validator.addSchema(schema.packageInfo, '/PackageInfo');
    validator.addSchema(schema.packageSchema, '/PackageSchema');
    validate(json, schema.packageArray, validator, 'package');
}

/**
 * Validates content.tirex.json
 */
function validateContentJson(json) {
    var validator = new jsonValidator();
    validator.addSchema(schema.advanceField, '/Advance');
    validator.addSchema(schema.resourceContentSchema, '/Content');
    validator.addSchema(schema.locationForDownload, '/LocationForDownload');
    validate(json, schema.contentArray, validator, 'content');
}

/**
 * Validates devices.tirex.json
 */
function validateDeviceJson(json) {
    var validator = new jsonValidator();
    validator.addSchema(schema.coreType, '/CoreType');
    validator.addSchema(schema.deviceSchema, '/Devices');
    validate(json, schema.deviceArray, validator, 'devices');
}

/**
 * Validates devtools.tirex.json
 */
function validateDevToolsJson(json) {
    var validator = new jsonValidator();
    validator.addSchema(schema.devtoolsSchema, '/Devtools');
    validate(json, schema.devToolsArray, validator, 'devtools');
}

/**
 * Validates json schema given the type of metadata it is
 * @param {JSON} json - the json to be validated
 * @param {string} filetype - type of metadata eg: devices, content,package
 */
var validateJsonSchema = exports.validateJsonSchema = function(json, fileType) {
    switch (fileType) {
        case 'content':
            validateContentJson(json);
            break;
        case 'package':
            validatePackageJson(json);
            break;
        case 'devices':
            validateDeviceJson(json);
            break;
        case 'devtools':
            validateDevToolsJson(json);
            break;
        case 'dependency':
            break;
        case 'macros':
            break;
        case 'devtools-aux':
            break;
        default:
            console.log('Invalid file name. Please rename the file according to its type.');
            break;
    }
};

var parseJson = exports.parseJson = function(data) {
    try {
        return jsonlint.parse(data);
    } catch (e) {
        console.log(e.message);
    }
};

if (require.main === module) {
    // gets filename from the command line.
    if (process.argv.length !== 3) {
        console.log('Usage: node ' + process.argv[1]+ ' FILENAME');
        process.exit(1);
    }
    var fileData = process.argv.slice(2);
    var file = new Object();
    file.name = fileData[0];

    var fragment = (process.platform === 'linux') ? (fileData[0].split('/').slice(-1)[0]).split('.') : (fileData[0].split('\\').slice(-1)[0]).split('.');
    file.type = fragment[fragment.length -3];
    fs.readFile(file.name, 'utf8', function (err, data) {
        if (err) throw err;
        validateJsonSchema(parseJson(data), file.type);
    });
}