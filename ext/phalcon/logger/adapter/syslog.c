
#ifdef HAVE_CONFIG_H
#include "../../../ext_config.h"
#endif

#include <php.h>
#include "../../../php_ext.h"
#include "../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/operators.h"
#include "kernel/array.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/object.h"
#include "kernel/exception.h"


/*
 +------------------------------------------------------------------------+
 | Phalcon Framework                                                      |
 +------------------------------------------------------------------------+
 | Copyright (c) 2011-2014 Phalcon Team (http://www.phalconphp.com)       |
 +------------------------------------------------------------------------+
 | This source file is subject to the New BSD License that is bundled     |
 | with this package in the file docs/LICENSE.txt.                        |
 |                                                                        |
 | If you did not receive a copy of the license and are unable to         |
 | obtain it through the world-wide-web, please send an email             |
 | to license@phalconphp.com so we can send you a copy immediately.       |
 +------------------------------------------------------------------------+
 | Authors: Andres Gutierrez <andres@phalconphp.com>                      |
 |          Eduar Carvajal <eduar@phalconphp.com>                         |
 +------------------------------------------------------------------------+
 */
/**
 * Phalcon\Logger\Adapter\Syslog
 *
 * Sends logs to the system logger
 *
 *<code>
 *	$logger = new \Phalcon\Logger\Adapter\Syslog("ident", array(
 *		'option' => LOG_NDELAY,
 *		'facility' => LOG_MAIL
 *	));
 *	$logger->log("This is a message");
 *	$logger->log("This is an error", \Phalcon\Logger::ERROR);
 *	$logger->error("This is another error");
 *</code>
 */
ZEPHIR_INIT_CLASS(Phalcon_Logger_Adapter_Syslog) {

	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Logger\\Adapter, Syslog, phalcon, logger_adapter_syslog, phalcon_logger_adapter_ce, phalcon_logger_adapter_syslog_method_entry, 0);

	zend_declare_property_bool(phalcon_logger_adapter_syslog_ce, SL("_opened"), 0, ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_class_implements(phalcon_logger_adapter_syslog_ce TSRMLS_CC, 1, phalcon_logger_adapterinterface_ce);
	return SUCCESS;

}

/**
 * Phalcon\Logger\Adapter\Syslog constructor
 *
 * @param string name
 * @param array options
 */
PHP_METHOD(Phalcon_Logger_Adapter_Syslog, __construct) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_0 = NULL;
	zval *name, *options = NULL, *option = NULL, *facility = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &name, &options);

	if (!options) {
		options = ZEPHIR_GLOBAL(global_null);
	}


	if (zephir_is_true(name)) {
		ZEPHIR_OBS_VAR(option);
		if (!(zephir_array_isset_string_fetch(&option, options, SS("option"), 0 TSRMLS_CC))) {
			ZEPHIR_INIT_NVAR(option);
			ZVAL_LONG(option, 4);
		}
		ZEPHIR_OBS_VAR(facility);
		if (!(zephir_array_isset_string_fetch(&facility, options, SS("facility"), 0 TSRMLS_CC))) {
			ZEPHIR_INIT_NVAR(facility);
			ZVAL_LONG(facility, 8);
		}
		ZEPHIR_CALL_FUNCTION(NULL, "openlog", &_0, name, option, facility);
		zephir_check_call_status();
		zephir_update_property_this(this_ptr, SL("_opened"), (1) ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Returns the internal formatter
 *
 * @return Phalcon\Logger\Formatter\Line
 */
PHP_METHOD(Phalcon_Logger_Adapter_Syslog, getFormatter) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *formatter;

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(formatter);
	zephir_read_property_this(&formatter, this_ptr, SL("_formatter"), PH_NOISY_CC);
	if (Z_TYPE_P(formatter) != IS_OBJECT) {
		ZEPHIR_INIT_BNVAR(formatter);
		object_init_ex(formatter, phalcon_logger_formatter_syslog_ce);
		if (zephir_has_constructor(formatter TSRMLS_CC)) {
			ZEPHIR_CALL_METHOD(NULL, formatter, "__construct", NULL);
			zephir_check_call_status();
		}
		zephir_update_property_this(this_ptr, SL("_formatter"), formatter TSRMLS_CC);
	}
	RETURN_CCTOR(formatter);

}

/**
 * Writes the log to the stream itself
 *
 * @param string message
 * @param int type
 * @param int time
 */
PHP_METHOD(Phalcon_Logger_Adapter_Syslog, logInternal) {

	zephir_nts_static zephir_fcall_cache_entry *_7 = NULL;
	zend_class_entry *_4;
	int type, time, ZEPHIR_LAST_CALL_STATUS;
	zval *message, *type_param = NULL, *time_param = NULL, *appliedFormat = NULL, *_0 = NULL, *_1, *_2, *_3, *_5, *_6;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &message, &type_param, &time_param);

	type = zephir_get_intval(type_param);
	time = zephir_get_intval(time_param);


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "getformatter",  NULL);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, type);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_LONG(_2, time);
	ZEPHIR_CALL_METHOD(&appliedFormat, _0, "format", NULL, message, _1, _2);
	zephir_check_call_status();
	if (Z_TYPE_P(appliedFormat) != IS_ARRAY) {
		ZEPHIR_INIT_VAR(_3);
		_4 = zend_fetch_class(SL("Phalcon\\Logger\\Adapter\\Exception"), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
		object_init_ex(_3, _4);
		if (zephir_has_constructor(_3 TSRMLS_CC)) {
			ZEPHIR_INIT_BNVAR(_1);
			ZVAL_STRING(_1, "The formatted message is not valid", 0);
			ZEPHIR_CALL_METHOD(NULL, _3, "__construct", NULL, _1);
			zephir_check_temp_parameter(_1);
			zephir_check_call_status();
		}
		zephir_throw_exception_debug(_3, "phalcon/logger/adapter/syslog.zep", 97 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_array_fetch_long(&_5, appliedFormat, 0, PH_NOISY | PH_READONLY TSRMLS_CC);
	zephir_array_fetch_long(&_6, appliedFormat, 1, PH_NOISY | PH_READONLY TSRMLS_CC);
	ZEPHIR_CALL_FUNCTION(NULL, "syslog", &_7, _5, _6);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Closes the logger
 *
 * @return boolean
 */
PHP_METHOD(Phalcon_Logger_Adapter_Syslog, close) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL;
	zval *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_opened"), PH_NOISY_CC);
	if (zephir_is_true(_0)) {
		ZEPHIR_CALL_FUNCTION(NULL, "closelog", &_1);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();

}

