/**
 * \file
 *
 * \brief Top level header file
 *
 * Copyright (c) 2020 Microchip Technology Inc.
 *
 * \license_start
 *
 * \page License
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * \license_stop
 *
 */

#ifndef _SAM_
#define _SAM_

#if defined(__SAMD20G17__) || defined(__ATSAMD20G17__)
  #define SAMD20
  #include "samd20/samd20g17.h"
#elif defined(__SAMD20J15__) || defined(__ATSAMD20J15__)
  #define SAMD20
  #include "samd20/samd20j15.h"
#elif defined(__SAMD20E14__) || defined(__ATSAMD20E14__)
  #define SAMD20
  #include "samd20/samd20e14.h"
#elif defined(__SAMD20G14__) || defined(__ATSAMD20G14__)
  #define SAMD20
  #include "samd20/samd20g14.h"
#elif defined(__SAMD20G18__) || defined(__ATSAMD20G18__)
  #define SAMD20
  #include "samd20/samd20g18.h"
#elif defined(__SAMD20J17__) || defined(__ATSAMD20J17__)
  #define SAMD20
  #include "samd20/samd20j17.h"
#elif defined(__SAMD20E17__) || defined(__ATSAMD20E17__)
  #define SAMD20
  #include "samd20/samd20e17.h"
#elif defined(__SAMD20G15__) || defined(__ATSAMD20G15__)
  #define SAMD20
  #include "samd20/samd20g15.h"
#elif defined(__SAMD20E15__) || defined(__ATSAMD20E15__)
  #define SAMD20
  #include "samd20/samd20e15.h"
#elif defined(__SAMD20E16__) || defined(__ATSAMD20E16__)
  #define SAMD20
  #include "samd20/samd20e16.h"
#elif defined(__SAMD20E18__) || defined(__ATSAMD20E18__)
  #define SAMD20
  #include "samd20/samd20e18.h"
#elif defined(__SAMD20J14__) || defined(__ATSAMD20J14__)
  #define SAMD20
  #include "samd20/samd20j14.h"
#elif defined(__SAMD20G18U__) || defined(__ATSAMD20G18U__)
  #define SAMD20
  #include "samd20/samd20g18u.h"
#elif defined(__SAMD20G16__) || defined(__ATSAMD20G16__)
  #define SAMD20
  #include "samd20/samd20g16.h"
#elif defined(__SAMD20J18__) || defined(__ATSAMD20J18__)
  #define SAMD20
  #include "samd20/samd20j18.h"
#elif defined(__SAMD20G17U__) || defined(__ATSAMD20G17U__)
  #define SAMD20
  #include "samd20/samd20g17u.h"
#elif defined(__SAMD20J16__) || defined(__ATSAMD20J16__)
  #define SAMD20
  #include "samd20/samd20j16.h"
#elif   defined(__SAMC21E15A__) || defined(__ATSAMC21E15A__)
  #define SAMC21
  #include "samc21/samc21e15a.h"
#elif defined(__SAMC21E16A__) || defined(__ATSAMC21E16A__)
  #define SAMC21
  #include "samc21/samc21e16a.h"
#elif defined(__SAMC21E17A__) || defined(__ATSAMC21E17A__)
  #define SAMC21
  #include "samc21/samc21e17a.h"
#elif defined(__SAMC21E18A__) || defined(__ATSAMC21E18A__)
  #define SAMC21
  #include "samc21/samc21e18a.h"
#elif defined(__SAMC21G15A__) || defined(__ATSAMC21G15A__)
  #define SAMC21
  #include "samc21/samc21g15a.h"
#elif defined(__SAMC21G16A__) || defined(__ATSAMC21G16A__)
  #define SAMC21
  #include "samc21/samc21g16a.h"
#elif defined(__SAMC21G17A__) || defined(__ATSAMC21G17A__)
  #define SAMC21
  #include "samc21/samc21g17a.h"
#elif defined(__SAMC21G18A__) || defined(__ATSAMC21G18A__)
  #define SAMC21
  #include "samc21/samc21g18a.h"
#elif defined(__SAMC21J15A__) || defined(__ATSAMC21J15A__)
  #define SAMC21
  #include "samc21/samc21j15a.h"
#elif defined(__SAMC21J16A__) || defined(__ATSAMC21J16A__)
  #define SAMC21
  #include "samc21/samc21j16a.h"
#elif defined(__SAMC21J17A__) || defined(__ATSAMC21J17A__)
  #define SAMC21
  #include "samc21/samc21j17a.h"
#elif defined(__SAMC21J18A__) || defined(__ATSAMC21J18A__)
  #define SAMC21
  #include "samc21/samc21j18a.h"
#else
#error Library does not support the specified device
#endif

#endif /* _SAM_ */
